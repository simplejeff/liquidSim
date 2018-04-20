#include "particle_system_world_entity.h"
#include <iostream>

ParticleSystemWorldEntity::ParticleSystemWorldEntity(ParticleSystemEntity * physics_entity,ParticleSystemRenderable * particle_renderable)
:WorldEntity(physics_entity,particle_renderable)
{
    ((ParticleSystemRenderable *)m_renderable_entity)->SetParticleSystemEntity((ParticleSystemEntity *)physics_entity);

}


ParticleSystemWorldEntity::~ParticleSystemWorldEntity()
{
    //dtor
}
