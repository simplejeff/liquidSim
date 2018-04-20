#ifndef SPHERE_COLLIDER_H
#define SPHERE_COLLIDER_H

#include "engine/entities/colliders/collider_entity.h"
#include "engine/entities/colliders/plane_collider.h"
#include "engine/entities/geometry/sphere.h"

class SphereCollider : public ColliderEntity
{
    public:
        SphereCollider(Sphere *,TransformEntity *);
        SphereCollider(Sphere *);
        virtual ~SphereCollider();
        Collision GetCollision(const ColliderEntity &) const;
        Collision GetCollision(const SphereCollider &) const;
        Collision GetCollision(const PlaneCollider &) const;

    protected:

    private:
};

#endif // SPHERE_COLLIDER_H
