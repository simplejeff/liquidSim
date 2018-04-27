#ifndef COLLISION_H
#define COLLISION_H

#include <Eigen/Core>
using namespace Eigen;

class Collision
{
    public:
        Collision();
        Collision(const Vector3f&,float,bool,float,float);
        virtual ~Collision();
        inline Vector3f GetNormal() const{return m_normal;}
        inline float GetDistance() const{ return m_distance;}
        inline bool IsValid() const{ return m_valid;}
        inline float GetFrictionCoeff() const{return m_friction_coeff;}
        inline float GetRestitutionCoeff() const{return m_restitution_coeff;}
    protected:
        Vector3f m_normal;
        float m_distance;
        bool m_valid;
        float m_friction_coeff;
        float m_restitution_coeff;
    private:
};

#endif // COLLISION_H
