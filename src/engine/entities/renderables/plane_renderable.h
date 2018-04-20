#ifndef PLANE_RENDERABLE_H
#define PLANE_RENDERABLE_H

#include "engine/entities/renderables/renderable_entity.h"
#include "engine/entities/geometry/plane_entity.h"

class PlaneRenderable : public RenderableEntity
{
    public:
        PlaneRenderable(PlaneEntity *);
        virtual ~PlaneRenderable();
        void Render(Graphics *g) const;
    protected:

    private:
};

#endif // PLANE_RENDERABLE_H
