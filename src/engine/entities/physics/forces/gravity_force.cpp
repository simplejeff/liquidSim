#include "engine/entities/physics/forces/gravity_force.h"
#include <Eigen/Core>
#include <iostream>

GravityForce::GravityForce()
{
    //ctor
    m_g << 0,-9.8,0;
}

void GravityForce::ApplyForce(DynamicPhysicsEntity & entity,float t){
    entity.AddForce(m_g.replicate(entity.GetDim(),1));
}


GravityForce::~GravityForce()
{
    //dtor
}
