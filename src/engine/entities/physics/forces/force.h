#ifndef FORCE_H
#define FORCE_H

#include <Eigen/Dense>
#include "engine/entities/physics/dynamics/dynamic_physics_entity.h"

using namespace Eigen;

class Force
{
    public:
        Force();
        virtual void ApplyForce(DynamicPhysicsEntity &,float) = 0; //Get on a dynamic entity at a given time
        virtual ~Force();

    protected:
        size_t m_size;
    private:
};

#endif // FORCE_H
