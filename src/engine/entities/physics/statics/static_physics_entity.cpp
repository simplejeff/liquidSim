#include "engine/entities/physics/statics/static_physics_entity.h"

StaticPhysicsEntity::StaticPhysicsEntity(ColliderEntity * collider,const Vector3f & offset,float scale):PhysicsEntity(collider),m_offset(offset),m_scale(scale){
    m_physics_entity_type = STATIC;
}


StaticPhysicsEntity::StaticPhysicsEntity(ColliderEntity * collider):StaticPhysicsEntity(collider,Vector3f(0,0,0),1)
{
    //ctor
}

StaticPhysicsEntity::~StaticPhysicsEntity()
{
    //dtor
}
