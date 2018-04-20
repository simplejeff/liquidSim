#ifndef CUBE_COLLIDER_H
#define CUBE_COLLIDER_H

#include "collider_entity.h"

class CubeCollider : public ColliderEntity
{
    public:
        CubeCollider(GeomEntity *);
        virtual ~CubeCollider();
        Collision GetCollision(const Vector3f&) const;

    protected:

    private:
};

#endif // CUBE_COLLIDER_H
