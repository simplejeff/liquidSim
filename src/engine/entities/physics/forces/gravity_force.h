#ifndef GRAVITYFORCE_H
#define GRAVITYFORCE_H

#include "engine/entities/physics/forces/force.h"


class GravityForce : public Force
{
    public:
        GravityForce();
        void ApplyForce(DynamicPhysicsEntity &,float);
        virtual ~GravityForce();

    protected:

    private:
        Vector3f m_g;
};

#endif // GRAVITYFORCE_H
