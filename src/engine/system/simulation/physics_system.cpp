#include "engine/system/simulation/physics_system.h"
#include <iostream>
#include "engine/entities/colliders/collider_entity.h"

PhysicsSystem::PhysicsSystem()
{
    //ctor
    m_time  = 0;
}


PhysicsSystem::~PhysicsSystem()
{
    //dtor
}


void PhysicsSystem::UpdateSystem(){
    ClearForces();
    CalculateForces();
    Gather();
}


void PhysicsSystem::ClearForces(){
    for(size_t i = 0;i<m_dynamic_entities.size();i++){
        m_dynamic_entities[i]->ClearForces();
    }
}

void PhysicsSystem::CalculateForces(){
    //Right now, dynamic entities are not colliding with each other, there are just dynamic-static interactions
    DynamicPhysicsEntity * dynamic_entity;
    for(size_t i = 0;i<m_dynamic_entities.size();i++){

        dynamic_entity = m_dynamic_entities[i];

        //Apply all of the forces
        for(size_t j = 0;j<m_forces.size();j++){
          m_forces[j]->ApplyForce(*(dynamic_entity),m_time);
        }

        //Perform collision detection and resolution
        for(size_t j = 0; j < m_static_entities.size();j++){
            dynamic_entity->HandleCollision(*(m_static_entities[j]));
        }
    }

}

void PhysicsSystem::Gather(){
    for(size_t i = 0;i<m_dynamic_entities.size();i++){
        m_dynamic_entities[i]->ComputeStateDerivative();
    }
}
