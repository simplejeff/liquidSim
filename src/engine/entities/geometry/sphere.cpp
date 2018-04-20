#include "engine/entities/geometry/sphere.h"
#include <GL/freeglut.h>

Sphere::Sphere(TransformEntity * transform_entity,const Vector3f & center,float radius):GeomEntity(transform_entity),m_center(center),m_radius(radius)
{
    //ctor
}

Sphere::~Sphere()
{
    //dtor
}


std::ostream& operator<<(std::ostream& s,Sphere & sphere){
    return s << "Center:\n" << sphere.GetCenter() << "\nRadius: " << sphere.GetRadius() << std::endl;
}
