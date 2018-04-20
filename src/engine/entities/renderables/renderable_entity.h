#ifndef RENDERABLEENTITY_H
#define RENDERABLEENTITY_H

#include "engine/entities/geometry/geom_entity.h"
#include "engine/entities/misc/transform_entity.h"
#include "engine/graphics/Graphics.h"
#include "engine/graphics/shape.h"


class RenderableEntity : public Entity
{
    public:
        RenderableEntity(const GeomEntity *);
        ~RenderableEntity();
        virtual void Render(Graphics *g) const = 0;
        inline GeomEntity const * GetGeomEntity() const{ return m_geom_entity;}
        inline void SetGeomEntity(GeomEntity * geom_entity){ m_geom_entity = geom_entity;}
        inline void SetColor(const Vector3f & color){m_color = color;}
    protected:
        const GeomEntity * m_geom_entity;
        std::shared_ptr<Shape> m_shape;
        Vector3f m_color;
    private:
};

#endif // RENDERABLEENTITY_H
