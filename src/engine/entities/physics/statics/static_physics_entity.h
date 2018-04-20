#ifndef STATICPHYSICSENTITY_H
#define STATICPHYSICSENTITY_H

#include "engine/entities/physics/physics_entity.h"
#include "engine/entities/physics/dynamics/dynamic_physics_entity.h"

class StaticPhysicsEntity : public PhysicsEntity
{
    public:
        StaticPhysicsEntity(ColliderEntity *,const Vector3f &,float);
        StaticPhysicsEntity(ColliderEntity *);
        inline Vector3f GetOffset() const{return m_offset;}
        inline float GetScale() const{return m_scale;}
        inline void SetOffset(const Vector3f& offset){m_offset = offset;}
        //virtual bool ResolveCollision(DynamicPhysicsEntity &) = 0;
        virtual ~StaticPhysicsEntity();
    protected:
        Vector3f m_offset;
        float m_scale;
    private:
};

#endif // STATICPHYSICSENTITY_H
