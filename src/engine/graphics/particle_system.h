#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "engine/util/common_includes.h"
#include "engine/graphics/shader_attrib_locations.h"
#include "graphics.h"
#include "src/engine/graphics/camera.h"

struct Particle {
    glm::vec3 pos;
    glm::vec3 speed;
    glm::vec3 forceAccum;
    glm::vec4 col;
    float mass;
    float size;
    float distance;
    bool operator<(Particle& that){
            // Sort in reverse order : far particles drawn first.
            return this->distance > that.distance;
        }
};

class ParticleSystem
{
public:
    ParticleSystem(std::shared_ptr<Camera> cam);
    ~ParticleSystem();
    void draw(Graphics *g);
    void tick(float time);
    void applyGravity(glm::vec3 gravitySphere);
private:
    float gravityForce = 2.0f;
    std::shared_ptr<Camera> m_camera;
    glm::vec3 m_gravity = glm::vec3(0.f, -1.f, 0.f);
    // particles
    GLuint m_particlesProgram;

    GLuint m_particlesVAO;
    int m_seaRowNum = 30;
    int m_seaColNum = 30;
    int m_seaHeightNum = 15;
    glm::vec3 m_seaSize;
    glm::vec3 m_seaTopLeft;
    int m_maxParticles;
    int m_particlesCount;
    GLuint m_billboard_vb;
    GLuint m_particles_position_vb;
    GLuint m_particles_color_vb;
    GLfloat* m_particles_position_data;
    GLubyte* m_particles_color_data;
    Particle* m_particlesContainer;
    float particleRadius = .01f;
    void renderParticles();
    void collisionTest(int particleId);
    glm::vec3 m_particle_mat = glm::vec3(0.064453125f*4.f, 0.1923828125f*4.f, 0.23828125f*4.f);
    glm::vec3 m_particle_mat_top = glm::vec3(.238f*4.f, .06445f*4.f, 0.21484f*4.f);
};

#endif // PARTICLESYSTEM_H
