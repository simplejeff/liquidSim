#ifndef PARTICLE_SYSTEM_WORLDENTITY_H
#define PARTICLE_SYSTEM_WORLDENTITY_H

#include "engine/entities/world/world_entity.h"
#include "engine/entities/physics/dynamics/particle_system_entity.h"
#include "engine/entities/renderables/particle_system_renderable.h"
#include "engine/entities/misc/transform_entity.h"


class ParticleSystemWorldEntity : public WorldEntity
{
    public:
        ParticleSystemWorldEntity(ParticleSystemEntity * ,ParticleSystemRenderable *);
        virtual ~ParticleSystemWorldEntity();

    protected:

    private:
};

#endif // PARTICLE_SYSTEM_WORLDENTITY_H
