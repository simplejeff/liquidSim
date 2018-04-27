#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "engine/graphics/Graphics.h"
#include  "src/engine/physics/constraint.h"
#include  "src/engine/physics/static_object.h"
#include  "src/engine/math/kernel.h"
#include  "src/engine/math/constraint_solver.h"
#include <Eigen/Core>
using namespace Eigen;


class ParticleSystem
{
    public:
        ParticleSystem(const VectorXf &,const VectorXf &,float,float,Kernel const *,Kernel const *,Grid *);
        virtual ~ParticleSystem();
        void Step(float);
        void Render(Graphics *g) const;
        inline void AddConstraint(Constraint * constraint){ m_constraints.push_back(constraint);}
        inline void AddStaticObject(StaticObject * object){ m_static_objects.push_back(object);}
        inline size_t GetNumParticles() const{return m_num_particles;}
        inline Vector3f GetParticlePosition(size_t index) const{size_t tri = 3*index; return Vector3f(m_x_new(tri),m_x_new(tri+1),m_x_new(tri+2));}
        inline Vector3f GetParticleVelocity(size_t index) const{size_t tri = 3*index; return Vector3f(m_v(tri),m_v(tri+1),m_v(tri+2));}
        inline void SetParticleOldPosition(size_t index,const Vector3f & x){size_t tri = 3*index; m_x(tri) = x(0); m_x(tri+1) = x(1); m_x(tri+2) = x(2);}
        inline void SetParticleNewPosition(size_t index,const Vector3f & x){size_t tri = 3*index; m_x_new(tri) = x(0); m_x_new(tri+1) = x(1); m_x_new(tri+2) = x(2);}
        inline void SetParticleVelocity(size_t index,const Vector3f & v){size_t tri = 3*index; m_v(tri) = v(0); m_v(tri+1) = v(1); m_v(tri+2) = v(2);}
        inline void SetParticleForce(size_t index,const Vector3f & f){size_t tri = 3*index; m_f(tri) = f(0); m_f(tri+1) = f(1); m_f(tri+2) = f(2);}

        inline Vector3f GetParticleForce(size_t index) const{size_t tri = 3*index; return Vector3f(m_f(tri),m_f(tri+1),m_f(tri+2));}
    protected:

    private:
        void ClearForces();
        void ApplyForces();
        void HandleCollisions();
        void HandleCollision(const std::vector<Collision> &,size_t);


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
        float particleRadius = .03f;
        glm::vec3 m_particle_mat = glm::vec3(0.064453125f*4.f, 0.1923828125f*4.f, 0.23828125f*4.f);
        glm::vec3 m_particle_mat_top = glm::vec3(.238f*4.f, .06445f*4.f, 0.21484f*4.f);


        VectorXf m_x;
        VectorXf m_x_new;
        VectorXf m_v;
        VectorXf m_f;
        VectorXf m_gravity;
        size_t m_num_particles;
        size_t m_num_entries;
        float m_render_radius;

        std::vector<Constraint *> m_constraints;
        std::vector<StaticObject *> m_static_objects;

        ConstraintSolver * m_solver;

};

#endif // PARTICLE_SYSTEM_H
