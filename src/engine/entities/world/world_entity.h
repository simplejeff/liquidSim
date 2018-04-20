#ifndef WORLD_ENTITY_H
#define WORLD_ENTITY_H

#include "engine/entities/entity.h"
#include "engine/entities/physics/physics_entity.h"
#include "engine/entities/renderables/renderable_entity.h"
#include "engine/entities/misc/transform_entity.h"

class WorldEntity : public Entity
{
    public:
        WorldEntity(PhysicsEntity *,RenderableEntity *);
        WorldEntity(PhysicsEntity *);
        WorldEntity(RenderableEntity *);
        virtual ~WorldEntity();
        inline bool IsPhysical(){ return (m_physics_entity != NULL);}
        inline bool IsRenderable(){ return (m_renderable_entity != NULL);}
        inline PhysicsEntity const * GetPhysicsEntity() const{return m_physics_entity;}
        inline RenderableEntity const * GetRenderableEntity() const{return m_renderable_entity;}

    protected:
        PhysicsEntity * m_physics_entity;
        RenderableEntity * m_renderable_entity;
    private:
};

#endif // WORLD_ENTITY_H
