#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "engine/entities/world/world_entity.h"

class Scene
{
    public:
        Scene();
        ~Scene();
        inline size_t GetNumEntities(){ return m_world_entities.size();}
        inline WorldEntity * GetEntity(int index) const{ return m_world_entities[index]; }
        inline std::vector<WorldEntity *> * GetEntities(){return &m_world_entities;}
        void AddEntity(WorldEntity * world_entity){m_world_entities.push_back(world_entity);}
    protected:
    private:
        std::vector<WorldEntity *> m_world_entities;

};

#endif // SCENE_H
