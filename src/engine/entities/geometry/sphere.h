#ifndef SPHEREENTITY_H
#define SPHEREENTITY_H

#include "engine/entities/geometry/geom_entity.h"
#include <ostream>
#include <Eigen/Dense>

using namespace Eigen;


class Sphere : public GeomEntity
{
    public:
        Sphere(TransformEntity *,const Vector3f &,float);
        virtual ~Sphere();
        Vector3f GetCenter() const{ return m_center;}
        float GetRadius() const{ return m_radius;}
        void SetCenter(const Vector3f & center){m_center = center;}
        void SetRadius(float radius){m_radius = radius;}
    protected:

    private:
        Vector3f m_center;
        float m_radius;
};

std::ostream& operator<<(std::ostream&,Sphere &);


#endif // SPHEREENTITY_H
