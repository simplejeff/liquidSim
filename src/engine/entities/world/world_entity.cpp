#include "engine/entities/world/world_entity.h"
#include <iostream>

WorldEntity::WorldEntity(PhysicsEntity * physics_entity,RenderableEntity * renderable_entity):
m_physics_entity(physics_entity),m_renderable_entity(renderable_entity)
{

}

WorldEntity::WorldEntity(PhysicsEntity * physics_entity):WorldEntity(physics_entity,NULL){}

WorldEntity::WorldEntity(RenderableEntity * renderable_entity):WorldEntity(NULL,renderable_entity){}

WorldEntity::~WorldEntity()
{
    //dtor
}
