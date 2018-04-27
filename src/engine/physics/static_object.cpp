#include "static_object.h"

StaticObject::StaticObject(float friction_coeff,float restitution_coeff):m_friction_coeff(friction_coeff),m_restitution_coeff(restitution_coeff),m_color(Vector3f(.5f,.5f,.5f))
{
    //ctor
}

StaticObject::~StaticObject()
{
    //dtor
}
