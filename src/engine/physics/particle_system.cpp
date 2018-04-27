#include "particle_system.h"
#include "engine/graphics/resource_loader.h"
#include <GL/freeglut.h>
#include  "src/engine/physics/density_constraint.h"
#include <iostream>

ParticleSystem::ParticleSystem(const VectorXf & x,const VectorXf & v,float render_radius,float rest_density,Kernel  const * value_kernel,Kernel const * grad_kernel,Grid * grid):
m_x(x),m_x_new(x),m_v(v),m_num_particles(m_x.rows()/3),m_num_entries(m_num_particles*3),m_render_radius(render_radius)
{
    //ctor
    m_f = VectorXf(m_num_entries,1);
    m_gravity = Vector3f(0,-9.8,0).replicate(m_num_particles,1);
    for(size_t i = 0;i<m_num_particles;i++){
        m_constraints.push_back(new DensityConstraint(i,rest_density,value_kernel,grad_kernel));
    }
    m_solver = new ConstraintSolver(.001,value_kernel,grad_kernel,grid,1.0);

    //particle billboarding
    std::cout << "num particles : " << m_num_particles << std::endl;
    m_maxParticles = m_num_particles;
    m_particles_position_data = new GLfloat[4*m_maxParticles];
    m_particles_color_data = new GLubyte[4*m_maxParticles];
    // vertex position VBO
        static const GLfloat particles_vb_data[] = {
            -1.0f, 1.0f, 0.0f,
            -1.0f, -1.0f, 0.0f,
             1.0f,  1.0f, 0.0f,
             1.0f, -1.0f, 0.0f,
        };
        glGenBuffers(1, &m_billboard_vb);
        glBindBuffer(GL_ARRAY_BUFFER, m_billboard_vb);
        glBufferData(GL_ARRAY_BUFFER, sizeof(particles_vb_data), particles_vb_data, GL_STATIC_DRAW);

        // particle position VBO
        glGenBuffers(1, &m_particles_position_vb);
        glBindBuffer(GL_ARRAY_BUFFER, m_particles_position_vb);
        glBufferData(GL_ARRAY_BUFFER, m_maxParticles*4*sizeof(GLfloat), NULL, GL_STREAM_DRAW);

        // particle color VBO
        glGenBuffers(1, &m_particles_color_vb);
        glBindBuffer(GL_ARRAY_BUFFER, m_particles_color_vb);
        glBufferData(GL_ARRAY_BUFFER, m_maxParticles*4*sizeof(GLubyte), NULL, GL_STREAM_DRAW);
        m_particlesProgram = ResourceLoader::loadShaders(
                    ":/shaders/particles.vert", ":/shaders/particles.frag");
}

ParticleSystem::~ParticleSystem()
{
    //dtor
    //dtor
    delete [] m_particles_position_data;
    delete [] m_particles_color_data;
}

void ParticleSystem::Step(float dt){

    m_x_new = m_x;

    ClearForces();
    ApplyForces();
    HandleCollisions();


    //Basic update
    m_v += dt*m_f;
    m_x_new += dt*m_v;

    //Constraint stuff goes here
    m_solver->SolverIterations(40,m_constraints,m_x_new);

    //Adjust original positions
    m_x = m_x_new;
}


void ParticleSystem::Render(Graphics *g) const{
    g->particleCheck(true);
    g->clearTransform();
    glEnable(GL_BLEND);
    glUseProgram(m_particlesProgram); // bind
    glUniformMatrix4fv(glGetUniformLocation(m_particlesProgram, "p"), 1, GL_FALSE, glm::value_ptr(g->getProj()));
    glUniformMatrix4fv(glGetUniformLocation(m_particlesProgram, "v"), 1, GL_FALSE, glm::value_ptr(g->getView()));
    glm::mat4x4 s = glm::scale(glm::vec3(1.f));
    glm::mat4x4 t = glm::translate(glm::vec3(0.f, 0.f, 0.f));
    glUniformMatrix4fv(glGetUniformLocation(m_particlesProgram, "particleScale"), 1, GL_FALSE, glm::value_ptr(s));
    glUniformMatrix4fv(glGetUniformLocation(m_particlesProgram, "particlePosition"), 1, GL_FALSE, glm::value_ptr(t));

    // VAO
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    for(size_t i = 0;i< m_num_particles;i++){
        int idx = i*4;
        // positions + size
        m_particles_position_data[idx+0] = m_x(i*3);
        m_particles_position_data[idx+1] = m_x(i*3+1);
        m_particles_position_data[idx+2] = m_x(i*3+2);
        m_particles_position_data[idx+3] = particleRadius;

        // colors
        float blend = ((m_x(i*3+1)+ 3.0f)/6.f);
        m_particles_color_data[idx+0] = (m_particle_mat.x*(1.f-blend) + m_particle_mat_top.x*blend)*255.f;
        m_particles_color_data[idx+1] = (m_particle_mat.y*(1.f-blend) + m_particle_mat_top.y*blend)*255.f;
        m_particles_color_data[idx+2] = (m_particle_mat.z*(1.f-blend) + m_particle_mat_top.z*blend)*255.f;
        m_particles_color_data[idx+3] = 220.f;
    }

    // update particle position
    glBindBuffer(GL_ARRAY_BUFFER, m_particles_position_vb);
    glBufferData(GL_ARRAY_BUFFER, m_maxParticles*4*sizeof(GLfloat), NULL, GL_STREAM_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_maxParticles*4*sizeof(GLfloat), m_particles_position_data);

    // update particle color
    glBindBuffer(GL_ARRAY_BUFFER, m_particles_color_vb);
    glBufferData(GL_ARRAY_BUFFER, m_maxParticles*4*sizeof(GLubyte), NULL, GL_STREAM_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_maxParticles*4*sizeof(GLubyte), m_particles_color_data);

    // set vertex attribute
    glEnableVertexAttribArray(0);   // quad vertices
    glBindBuffer(GL_ARRAY_BUFFER, m_billboard_vb);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);

    // set particle position attribute
    glEnableVertexAttribArray(1);   // position
    glBindBuffer(GL_ARRAY_BUFFER, m_particles_position_vb);
    glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, 0);

    // set particle color attribute
    glEnableVertexAttribArray(2);   // color
    glBindBuffer(GL_ARRAY_BUFFER, m_particles_color_vb);
    glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, false, 0, 0);
    //glBindTexture()
    // draw particles (glDrawArrays ParticlesCount times)
    glVertexAttribDivisor(0, 0);
    glVertexAttribDivisor(1, 1);    // update
    glVertexAttribDivisor(2, 1);    // update
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, m_maxParticles);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    glUseProgram(0); // unbind
    glDisable(GL_BLEND);
    g->particleCheck(false);
    g->clearTransform();
    g->clearShader();
    g->setDefaultMaterial();

    for(size_t i = 0; i < m_static_objects.size();i++){
        m_static_objects[i]->Render(g);
    }

}


void ParticleSystem::ClearForces(){
    m_f = MatrixXf::Zero(m_num_entries,1);
}


void ParticleSystem::ApplyForces(){
    m_f += m_gravity;
}

void ParticleSystem::HandleCollisions(){
  for(size_t j = 0; j < m_num_particles;j++){
        Vector3f p = GetParticlePosition(j);
        for(size_t i = 0; i < m_static_objects.size();i++){
            std::vector<Collision> collisions = m_static_objects[i]->GetCollision(p);
            HandleCollision(collisions,j);
        }
    }
}

void ParticleSystem::HandleCollision(const std::vector<Collision> & collisions,size_t j){
    for(Collision collision : collisions) {
        if(collision.IsValid()){
            Vector3f p = GetParticlePosition(j);
            Vector3f v = GetParticleVelocity(j);
            Vector3f f = GetParticleForce(j);
            Vector3f n = collision.GetNormal();
            Vector3f v_n = v.dot(n)*n;
            Vector3f v_t = v - v_n;
            float dist = collision.GetDistance();
            if(fabs(dist) <= .2){
                if((fabs(v.dot(n)) < .5)){ //Contact
                    SetParticleForce(j,-collision.GetFrictionCoeff()*v_t*(- f.dot(n)));
                  //  SetParticleVelocity(j, v_t*collision.GetFrictionCoeff() - collision.GetRestitutionCoeff()*v_n);
                }else{
                    SetParticleVelocity(j,v_t - collision.GetRestitutionCoeff()*v_n);
                }
            }
            if(dist <= 0){
                SetParticleNewPosition(j,p + n*(.01f - dist));
            }
        }
    }
}

