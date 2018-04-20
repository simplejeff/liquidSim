#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include "engine/entities/physics/dynamics/dynamic_physics_entity.h"
#include "engine/entities/physics/statics/static_physics_entity.h"
#include <vector>
#include "engine/entities/physics/forces/force.h"


class PhysicsSystem
{
    public:
        PhysicsSystem();
        virtual ~PhysicsSystem();
        void UpdateSystem();
        inline void AddStaticEntity(StaticPhysicsEntity * entity){ m_static_entities.push_back(entity);}
        inline void AddDynamicEntity(DynamicPhysicsEntity * entity){ m_dynamic_entities.push_back(entity);}
        inline void AddForce(Force * force){m_forces.push_back(force);}
        inline StaticPhysicsEntity * GetStaticEntity(size_t index){return m_static_entities[index];}
        inline DynamicPhysicsEntity * GetDynamicEntity(size_t index){return m_dynamic_entities[index];}
        inline size_t GetNumDynamicEntities() const{return m_dynamic_entities.size();}
        inline size_t GetNumStaticEntities() const{return m_static_entities.size();}
        inline float GetTime() const{ return m_time;}
        inline void SetTime(float time){m_time = time;}
    protected:
        void ClearForces();
        void CalculateForces();
        void Gather();
        std::vector<StaticPhysicsEntity *> m_static_entities;
        std::vector<DynamicPhysicsEntity *> m_dynamic_entities;
        std::vector<Force *> m_forces;
    private:
        float m_time;
};

#endif // PHYSICSSYSTEM_H
