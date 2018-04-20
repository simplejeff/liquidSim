#ifndef SPHERE_RENDERABLE_H
#define SPHERE_RENDERABLE_H

#include "engine/entities/renderables/renderable_entity.h"
#include "engine/entities/geometry/sphere.h"
#include "engine/entities/misc/transform_entity.h"

class SphereRenderable : public RenderableEntity
{
    public:
        SphereRenderable(Sphere*);
        virtual ~SphereRenderable();
        void Render(Graphics *g) const;
    protected:

    private:
};

#endif // SPHERE_RENDERABLE_H
