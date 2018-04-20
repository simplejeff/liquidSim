#ifndef SOLVER_H
#define SOLVER_H

#include "engine/entities/physics/dynamics/dynamic_physics_entity.h"
#include "engine/system/simulation/physics_system.h"

enum SolverType{EULER,MIDPOINT,RK4};


class Solver
{
    public:
        Solver();
        static void Euler(PhysicsSystem &,float);
        virtual ~Solver();

    protected:

    private:
};

#endif // SOLVER_H
