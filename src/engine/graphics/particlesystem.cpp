#include "ParticleSystem.h"
#include "engine/graphics/ResourceLoader.h"
#include "glm/gtx/transform.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"
#include "GL/glew.h"
#include <QGLWidget>
#include <cstdlib>
#include <ctime>
ParticleSystem::ParticleSystem(std::shared_ptr<Camera> cam)
{
    srand (static_cast <unsigned> (time(0)));
    m_camera = cam;
    m_maxParticles = m_seaRowNum*m_seaColNum*m_seaHeightNum;
    m_particles_position_data = new GLfloat[4*m_maxParticles];
    m_particles_color_data = new GLubyte[4*m_maxParticles];
    m_particlesContainer = new Particle[m_maxParticles];

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
    glm::vec3 camPos = m_camera->getEye();
    // init particles
    m_seaSize = glm::vec3(6.f, 2.f, 6.f); // (width, height)
    m_seaTopLeft = glm::vec3(-m_seaSize.x/2.f, 0.1f, -m_seaSize.z/2.f);
    float distX = m_seaSize.x/m_seaColNum;
    float distY = m_seaSize.y/m_seaHeightNum;
    float distZ = m_seaSize.z/m_seaRowNum;
    m_particlesCount = m_maxParticles;
    for (int row = 0; row < m_seaRowNum; row++) {
        for (int col = 0; col < m_seaColNum; col++) {
            for (int y = 0; y <m_seaHeightNum; y++) {
                int idx = row*m_seaColNum*m_seaHeightNum + col*m_seaHeightNum + y;
                Particle p = Particle();
                p.pos = glm::vec3(m_seaTopLeft.x + distX*col, m_seaTopLeft.y + distY*y, m_seaTopLeft.z + distZ*row);
                float r1 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/.3f));
                float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/.3f));
                float r3 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/.3f));
                p.speed = glm::vec3(r1 - .15f, r2 - .15f, r3 - .15f);
                float blend = ((p.pos.y - m_seaTopLeft.y)/m_seaSize.y);
                (p.col)[0] = (m_particle_mat.x*(1.f-blend) + m_particle_mat_top.x*blend)*255.f;
                (p.col)[1]= (m_particle_mat.y*(1.f-blend) + m_particle_mat_top.y*blend)*255.f;
                (p.col)[2] = (m_particle_mat.z*(1.f-blend) + m_particle_mat_top.z*blend)*255.f;
                (p.col)[3] = 200.f;
                p.forceAccum = glm::vec3(0.f, 0.f, 0.f);
                p.mass = 1.f;
                p.size = particleRadius;
                p.distance = glm::length2(p.pos - camPos);
                m_particlesContainer[idx] = p;
                }
        }
    }

    m_particlesProgram = ResourceLoader::loadShaders(
                ":/shaders/particles.vert", ":/shaders/particles.frag");
}
ParticleSystem::~ParticleSystem()
{
    delete [] m_particles_position_data;
    delete [] m_particles_color_data;
    delete [] m_particlesContainer;
}

void ParticleSystem::collisionTest(int particleId) {
    Particle p = m_particlesContainer[particleId];
    if(p.pos.y <= particleRadius) {
        p.pos = glm::vec3(p.pos.x, 0.001f + particleRadius, p.pos.z);
        p.speed = glm::vec3(p.speed.x, -p.speed.y*.9f, p.speed.z);
    }
    if(p.pos.x <= -3.f + particleRadius) {
        p.pos = glm::vec3(-2.999f + particleRadius, p.pos.y, p.pos.z);
        p.speed = glm::vec3(-p.speed.x, p.speed.y, p.speed.z);
    }
    if(p.pos.x >= 3.f - particleRadius) {
        p.pos = glm::vec3(2.999f - particleRadius, p.pos.y, p.pos.z);
        p.speed = glm::vec3(-p.speed.x, p.speed.y, p.speed.z);
    }
    if(p.pos.z <= -3.f) {
        p.pos = glm::vec3(p.pos.x, p.pos.y, -2.999f);
        p.speed = glm::vec3(p.speed.x, p.speed.y, -p.speed.z);
    }
    if(p.pos.z >= 3.f) {
        p.pos = glm::vec3(p.pos.x, p.pos.y, 2.999f);
        p.speed = glm::vec3(p.speed.x, p.speed.y, -p.speed.z);
    }
    m_particlesContainer[particleId] = p;
}

void ParticleSystem::tick(float time) {
    glm::vec3 camPos = m_camera->getEye();
   for(int idx = 0; idx < m_maxParticles; idx++) {
              //  int idx = row*m_seaColNum*m_seaHeightNum + col*m_seaHeightNum + y;
                Particle p = m_particlesContainer[idx];
                p.speed += (p.forceAccum/p.mass + m_gravity) * time;
                p.pos += p.speed * time;
                m_particlesContainer[idx] = p;
                collisionTest(idx);
                p = m_particlesContainer[idx];
                float blend = ((p.pos.y - m_seaTopLeft.y)/m_seaSize.y);
                (p.col)[0] = (m_particle_mat.x*(1.f-blend) + m_particle_mat_top.x*blend)*255.f;
                (p.col)[1]= (m_particle_mat.y*(1.f-blend) + m_particle_mat_top.y*blend)*255.f;
                (p.col)[2] = (m_particle_mat.z*(1.f-blend) + m_particle_mat_top.z*blend)*255.f;
                p.distance = glm::length2(p.pos - camPos);
                m_particlesContainer[idx] = p;

    }
}

void ParticleSystem::draw(Graphics *g) {
    glEnable(GL_BLEND);
    glUseProgram(m_particlesProgram); // bind
    glUniformMatrix4fv(glGetUniformLocation(m_particlesProgram, "p"), 1, GL_FALSE, glm::value_ptr(g->getProj()));
    glUniformMatrix4fv(glGetUniformLocation(m_particlesProgram, "v"), 1, GL_FALSE, glm::value_ptr(g->getView()));
    glm::mat4x4 s = glm::scale(glm::vec3(1.f));
    glm::mat4x4 t = glm::translate(glm::vec3(0.f, 0.f, 0.f));
    glUniformMatrix4fv(glGetUniformLocation(m_particlesProgram, "particleScale"), 1, GL_FALSE, glm::value_ptr(s));
    glUniformMatrix4fv(glGetUniformLocation(m_particlesProgram, "particlePosition"), 1, GL_FALSE, glm::value_ptr(t));
    renderParticles();
    glUseProgram(0); // unbind
    glDisable(GL_BLEND);
}

void ParticleSystem::renderParticles() {
    // VAO
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    std::sort(&m_particlesContainer[0], &m_particlesContainer[m_maxParticles]);
    // update
    for (int idxindex = 0; idxindex < m_maxParticles; idxindex++) {
             //   int idx = row*m_seaColNum*m_seaHeightNum + col*m_seaHeightNum + y;
                Particle p = m_particlesContainer[idxindex];

                int idx = idxindex*4;

                // positions + size
                m_particles_position_data[idx+0] = p.pos.x;
                m_particles_position_data[idx+1] = p.pos.y;
                m_particles_position_data[idx+2] = p.pos.z;
                m_particles_position_data[idx+3] = p.size;

                // colors
                m_particles_color_data[idx+0] = p.col[0];
                m_particles_color_data[idx+1] = p.col[1];
                m_particles_color_data[idx+2] = p.col[2];
                m_particles_color_data[idx+3] = p.col[3];
    }

    // update particle position
    glBindBuffer(GL_ARRAY_BUFFER, m_particles_position_vb);
    glBufferData(GL_ARRAY_BUFFER, m_maxParticles*4*sizeof(GLfloat), NULL, GL_STREAM_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_particlesCount*4*sizeof(GLfloat), m_particles_position_data);

    // update particle color
    glBindBuffer(GL_ARRAY_BUFFER, m_particles_color_vb);
    glBufferData(GL_ARRAY_BUFFER, m_maxParticles*4*sizeof(GLubyte), NULL, GL_STREAM_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_particlesCount*4*sizeof(GLubyte), m_particles_color_data);

    // set vertex attribute
    glEnableVertexAttribArray(0);   // quad vertices
    glBindBuffer(GL_ARRAY_BUFFER, m_billboard_vb);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);

    // set particle positon attribute
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
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, m_particlesCount);
/*
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);*/


}

