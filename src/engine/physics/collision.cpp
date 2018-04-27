#include "collision.h"

Collision::Collision():m_valid(false){

}

Collision::Collision(const Vector3f& normal,float distance,bool valid,float friction_coeff,float restitution_coeff):
m_normal(normal),m_distance(distance),m_valid(valid),m_friction_coeff(friction_coeff),m_restitution_coeff(restitution_coeff)
{
    //ctor
}

Collision::~Collision()
{
    //dtor
}
