#ifndef CUBE_RENDERABLE_H
#define CUBE_RENDERABLE_H
#include "src/engine/graphics/Graphics.h"
class CubeRenderable
{
    public:
        CubeRenderable();
        virtual ~CubeRenderable();
        void Render(Graphics *g) const;
    protected:

    private:
};

#endif // CUBE_RENDERABLE_H
