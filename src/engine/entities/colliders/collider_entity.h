#ifndef COLLIDERENTITY_H
#define COLLIDERENTITY_H

#include "engine/entities/misc/transform_entity.h"
#include "engine/entities/geometry/geom_entity.h"
#include "engine/system/collision/collision.h"



class ColliderEntity : public Entity
{
    public:
        ColliderEntity(GeomEntity *);
        virtual ~ColliderEntity();
        inline GeomEntity const * GetGeomEntity() const{return m_geom_entity;}
        inline void SetGeomEntity(GeomEntity * geom_entity){ m_geom_entity = geom_entity;}
        virtual Collision GetCollision(const ColliderEntity &) const{ return Collision();}
        virtual Collision GetCollision(const Vector3f&) const = 0;
    protected:
        GeomEntity *m_geom_entity;
    private:
};

#endif // COLLIDERENTITY_H
