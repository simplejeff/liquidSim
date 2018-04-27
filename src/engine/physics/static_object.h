#ifndef STATIC_OBJECT_H
#define STATIC_OBJECT_H

#include "engine/graphics/Graphics.h"
#include "engine/graphics/shape.h"
#include  "src/engine/physics/collision.h"

class StaticObject
{
    public:
        StaticObject(float,float);
        virtual ~StaticObject();
        virtual std::vector<Collision> GetCollision(const Vector3f &) const = 0;
        virtual void Render(Graphics *g) const = 0;
        inline void SetColor(const Vector3f & color){m_color = color;}
    protected:
        std::shared_ptr<Shape> m_shape;
        Vector3f m_color;
        float m_friction_coeff;
        float m_restitution_coeff;
    private:
};

#endif // STATIC_OBJECT_H
