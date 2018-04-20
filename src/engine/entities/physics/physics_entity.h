#ifndef PHYSICSENTITY_H
#define PHYSICSENTITY_H

#include <Eigen/Dense>
#include "engine/entities/colliders/collider_entity.h"
#include "engine/entities/entity.h"
#include <vector>

using namespace Eigen;

enum PhysicsEntityType{STATIC,DYNAMIC};


class PhysicsEntity : public Entity
{
    public:
        PhysicsEntity(ColliderEntity *);
        virtual ~PhysicsEntity();
        inline ColliderEntity const * GetColliderEntity() const{ return m_collider_entity;}
        inline void SetColliderEntity(ColliderEntity * collider_entity){ m_collider_entity = collider_entity;}
        inline bool HasCollider() const{ return (m_collider_entity != NULL);}
        inline PhysicsEntityType GetPhysicsEntityType() const{ return m_physics_entity_type;}
        inline float GetCoefficientRestitution() const{ return m_coefficient_restitution;}
        inline void SetCoefficientRestitution(float coeff){ m_coefficient_restitution = coeff;}
        inline float GetCoefficientFriction() const{ return m_coefficient_friction;}
        inline void SetCoefficientFriction(float coeff){ m_coefficient_friction = coeff;}
    protected:
        ColliderEntity * m_collider_entity;
        PhysicsEntityType m_physics_entity_type;
        float m_coefficient_restitution;
        float m_coefficient_friction;
    private:
};

#endif // PHYSICSENTITY_H
