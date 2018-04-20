#ifndef SIMULATION_H
#define SIMULATION_H

#include "engine/system/simulation/physics_system.h"
#include "engine/system/simulation/solver.h"
#include "engine/scene/scene.h"
#include "engine/entities/world/world_entity.h"

class Simulation
{
    public:
        Simulation(SolverType,PhysicsSystem *);
        virtual ~Simulation();
        void Update(float time);
        void AddPhysicsEntity(WorldEntity &);
        void AddSceneEntities(Scene &);
        inline void ToggleActive(){ active = !active;}
        inline bool IsActive() const{return active;}
    protected:
        SolverType m_solver_type;
        PhysicsSystem * m_system;
        Solver m_solver;
        float dt;
        bool active;
    private:
};

#endif // SIMULATION_H
