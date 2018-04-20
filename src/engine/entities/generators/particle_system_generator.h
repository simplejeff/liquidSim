#ifndef PARTICLE_SYSTEM_GENERATOR_H
#define PARTICLE_SYSTEM_GENERATOR_H

#include "engine/entities/entity.h"
#include "engine/entities/world/particle_system_world_entity.h"



class ParticleSystemGenerator : public Entity
{
    public:
        ParticleSystemGenerator();
        ParticleSystemWorldEntity * GenerateCubeOfSpheres(const Vector3f&,const Vector3f&,const Vector3f&,size_t,const Vector3f &,float,float,bool);
        virtual ~ParticleSystemGenerator();

    protected:

    private:
        size_t CubeIndex(size_t,size_t,size_t,size_t) const;
};

#endif // PARTICLE_SYSTEM_GENERATOR_H
