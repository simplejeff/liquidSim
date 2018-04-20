#ifndef PLANE_COLLIDER_H
#define PLANE_COLLIDER_H

#include "engine/entities/colliders/plane_collider.h"
#include "engine/entities/colliders/collider_entity.h"

class PlaneCollider : public ColliderEntity
{
    public:
        PlaneCollider(GeomEntity *);
        virtual ~PlaneCollider();
        Collision GetCollision(const Vector3f&) const;
    protected:

    private:
};

#endif // PLANE_COLLIDER_H
