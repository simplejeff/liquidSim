#include "engine/renderer/renderer.h"
#include <stdlib.h>
#include <iostream>

Renderer::Renderer(Scene * scene)
{
    //ctor
    p_world_entities = scene->GetEntities();

}

void Renderer::Render(Graphics *g){
    for(size_t i = 0;i<p_world_entities->size();i++){
        WorldEntity * world_entity = p_world_entities->at(i);
        if(world_entity->IsRenderable()){
            const RenderableEntity * renderable_entity = world_entity->GetRenderableEntity();
            renderable_entity->Render(g);
        }
    }
}

Renderer::~Renderer()
{
    //dtor
    p_world_entities = NULL; //It is the scenes responsibility to delete the renderable_entities
}
