#include "engine/system/simulation/simulation.h"
#include <iostream>

Simulation::Simulation(SolverType solver_type,PhysicsSystem * system):m_solver_type(solver_type),m_system(system)
{
    //ctor
    dt = .01;
    active = true;
}


void Simulation::Update(float time){
    if(active){
        if(m_solver_type == EULER) m_solver.Euler(*m_system,time);
    }
}

void Simulation::AddPhysicsEntity(WorldEntity & entity){
    if(entity.IsPhysical()){
        const PhysicsEntity * physics_entity = entity.GetPhysicsEntity();
        if(physics_entity->GetPhysicsEntityType() == DYNAMIC){
            m_system->AddDynamicEntity((DynamicPhysicsEntity *)physics_entity);
        }else if(physics_entity->GetPhysicsEntityType() == STATIC){
            m_system->AddStaticEntity((StaticPhysicsEntity *)physics_entity);
        }
    }
}

void Simulation::AddSceneEntities(Scene & scene){
    for(size_t i = 0;i < scene.GetNumEntities();i++){
        WorldEntity * world_entity = scene.GetEntity(i);
        AddPhysicsEntity(*world_entity);
    }
}



Simulation::~Simulation()
{
    //dtor
}
