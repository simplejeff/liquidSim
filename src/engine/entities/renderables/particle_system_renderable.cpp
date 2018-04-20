#include "particle_system_renderable.h"
#include "engine/graphics/resource_loader.h"
#include <GL/freeglut.h>
#include <iostream>

ParticleSystemRenderable::ParticleSystemRenderable(RenderableEntity * particle_renderable_entity):RenderableEntity(particle_renderable_entity->GetGeomEntity()),m_particle_renderable_entity(particle_renderable_entity){}



ParticleSystemRenderable::~ParticleSystemRenderable()
{
    //dtor
    delete [] m_particles_position_data;
    delete [] m_particles_color_data;
}

void ParticleSystemRenderable::SetParticleSystemEntity(ParticleSystemEntity * particle_system_entity){
    m_particle_system_entity = particle_system_entity;
    m_maxParticles = m_particle_system_entity->GetDim();
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

void ParticleSystemRenderable::Render(Graphics *g) const{
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
    for(size_t i = 0;i<m_particle_system_entity->GetDim();i++){
        Vector3f pos = m_particle_system_entity->GetPosition(i);
        int idx = i*4;
        // positions + size
        m_particles_position_data[idx+0] = pos(0);
        m_particles_position_data[idx+1] = pos(1);
        m_particles_position_data[idx+2] = pos(2);
        m_particles_position_data[idx+3] = particleRadius;

        // colors
        float blend = ((pos(1)+ 3.0f)/6.f);
        m_particles_color_data[idx+0] = (m_particle_mat.x*(1.f-blend) + m_particle_mat_top.x*blend)*255.f;
        m_particles_color_data[idx+1] = (m_particle_mat.y*(1.f-blend) + m_particle_mat_top.y*blend)*255.f;
        m_particles_color_data[idx+2] = (m_particle_mat.z*(1.f-blend) + m_particle_mat_top.z*blend)*255.f;
        m_particles_color_data[idx+3] = 220.f;
//        g->translate(glm::vec3(pos(0),pos(1),pos(2)));
//        m_particle_renderable_entity->Render(g);
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
}

