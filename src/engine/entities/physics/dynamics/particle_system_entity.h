#ifndef PARTICLESYSTEMENTITY_H
#define PARTICLESYSTEMENTITY_H

#include "engine/entities/physics/dynamics/dynamic_physics_entity.h"
#include "engine/entities/renderables/renderable_entity.h"


class ParticleSystemEntity : public DynamicPhysicsEntity
{
    public:
        ParticleSystemEntity(ColliderEntity *,const VectorXf &,const VectorXf &);
        void HandleCollision(const PhysicsEntity &);

        virtual ~ParticleSystemEntity();
    protected:
    private:
        Collision GetCollision(const Vector3f&,const PhysicsEntity &) const;
        void ResolveCollision(size_t,const Collision &);
};

#endif // PARTICLESYSTEMENTITY_H
