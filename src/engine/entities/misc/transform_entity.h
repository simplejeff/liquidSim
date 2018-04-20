#ifndef TRANSFORM_ENTITY_H
#define TRANSFORM_ENTITY_H

#include <Eigen/Dense>
#include "engine/entities/entity.h"

using namespace Eigen;


class TransformEntity : public Entity
{
    public:
        TransformEntity();
        ~TransformEntity();
        inline Vector3f GetTranslate() const{return m_translate;}
        inline Vector3f GetScale() const{return m_scale;}
        inline Vector3f GetRotation() const{return m_rotation;}
        inline void SetTranslate(const Vector3f translate){m_translate = translate;}
        inline void SetScale(const Vector3f scale){m_scale = scale;}
        inline void SetRotation(const Vector3f rotation){m_rotation = rotation;}
    protected:
        Vector3f m_translate;
        Vector3f m_rotation;
        Vector3f m_scale;
    private:
};

#endif // TRANSFORM_ENTITY_H
