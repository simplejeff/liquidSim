#include "engine/system/simulation/solver.h"
#include <iostream>

Solver::Solver()
{
    //ctor
}

void Solver::Euler(PhysicsSystem & system,float dt){
    float t = system.GetTime();
    system.UpdateSystem(); //Computes derivatives of the system
    DynamicPhysicsEntity * entity;
    for(size_t i = 0; i < system.GetNumDynamicEntities();i++){
        entity = system.GetDynamicEntity(i);
        const VectorXf & q = entity->GetState();
        const VectorXf & dq = entity->GetDerivativeState();
        entity->SetState(q + dt*dq);
    }
    system.SetTime(t+dt);
}



Solver::~Solver()
{
    //dtor
}
