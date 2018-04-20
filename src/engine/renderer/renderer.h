#ifndef RENDERER_H
#define RENDERER_H

#include "engine/scene/scene.h"
#include <vector>
#include "engine/entities/renderables/renderable_entity.h"
#include "engine/graphics/Graphics.h"

class Renderer
{
    public:
        Renderer(Scene * );
        void Render(Graphics *g);
        virtual ~Renderer();

    protected:
    private:
        std::vector<WorldEntity *> * p_world_entities;
};

#endif // RENDERER_H
