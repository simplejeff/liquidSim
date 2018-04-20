#ifndef COLLISION_H
#define COLLISION_H

#include <Eigen/Dense>
#include <algorithm>
using namespace Eigen;

class Collision
{
    public:
        Collision();
        Collision(const Vector3f &,float,bool);
        virtual ~Collision();
        inline Vector3f GetNormal() const{ return m_normal;}
        inline float GetCollisionDistance() const{return m_collision_distance;}
        inline bool IsCollision() const{return m_is_collision;}
        inline float GetCoefficientRestitution() const{return m_coefficient_restitution;}
        inline void SetCoefficientRestitution(float coeff_a,float coeff_b){ m_coefficient_restitution = std::min(coeff_a,coeff_b);}
        inline float GetCoefficientFriction() const{return m_coefficient_friction;}
        inline void SetCoefficientFriction(float coeff_a,float coeff_b){ m_coefficient_friction = std::min(coeff_a,coeff_b);}
    protected:

    private:
        Vector3f m_normal;
        float m_collision_distance;
        bool m_is_collision;
        float m_coefficient_restitution;
        float m_coefficient_friction;
};

#endif // COLLISION_H
