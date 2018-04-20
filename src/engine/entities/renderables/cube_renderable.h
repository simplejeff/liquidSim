#ifndef CUBE_RENDERABLE_H
#define CUBE_RENDERABLE_H

#include "engine/entities/renderables/renderable_entity.h"


class CubeRenderable : public RenderableEntity
{
    public:
        CubeRenderable(GeomEntity *);
        virtual ~CubeRenderable();
        void Render(Graphics *g) const;
    protected:

    private:
};

#endif // CUBE_RENDERABLE_H
