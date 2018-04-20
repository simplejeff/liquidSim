#ifndef GEOM_ENTITY_H
#define GEOM_ENTITY_H

#include "engine/entities/entity.h"
#include "engine/entities/misc/transform_entity.h"

class GeomEntity : public Entity
{
    public:
        GeomEntity(TransformEntity *);
        virtual ~GeomEntity();
        inline TransformEntity const * GetTransformEntity() const{return m_transform_entity;}
    protected:

        TransformEntity * m_transform_entity;
    private:
};

#endif // GEOM_ENTITY_H
