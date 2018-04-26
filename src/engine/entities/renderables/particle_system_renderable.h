#ifndef PARTICLE_SYSTEM_RENDERABLE_H
#define PARTICLE_SYSTEM_RENDERABLE_H

#include "engine/entities/renderables/renderable_entity.h"
#include "engine/entities/physics/dynamics/particle_system_entity.h"

class ParticleSystemRenderable : public RenderableEntity
{
    public:
        ParticleSystemRenderable(RenderableEntity *);
        virtual ~ParticleSystemRenderable();
        void SetParticleSystemEntity(ParticleSystemEntity * particle_system_entity);
        void Render(Graphics *g) const;
    protected:

    private:
        int m_maxParticles = 0;
        Matrix4f view;
        Matrix4f proj;
        GLuint m_particlesProgram;
        GLuint m_particlesVAO;
        GLuint m_billboard_vb;
        GLuint m_particles_position_vb;
        GLuint m_particles_color_vb;
        GLfloat* m_particles_position_data;
        GLubyte* m_particles_color_data;
        float particleRadius = .02f;
        glm::vec3 m_particle_mat = glm::vec3(0.064453125f*4.f, 0.1923828125f*4.f, 0.23828125f*4.f);
        glm::vec3 m_particle_mat_top = glm::vec3(.238f*4.f, .06445f*4.f, 0.21484f*4.f);

        ParticleSystemEntity * m_particle_system_entity;
        RenderableEntity * m_particle_renderable_entity;
};

#endif // PARTICLE_SYSTEM_RENDERABLE_H
