#ifndef CUBE_ENTITY_H
#define CUBE_ENTITY_H

#include "geom_entity.h"

#include <Eigen/Dense>

using namespace Eigen;

class CubeEntity : public GeomEntity
{
    public:
        CubeEntity(TransformEntity *,const float width,const Vector3f &,const Vector3f&, const Vector3f &);
        virtual ~CubeEntity();
        inline float GetWidth() const{return m_w;}
        inline Vector3f GetV0() const{return m_v0;}
        inline Vector3f GetV1() const{return m_v1;}
        inline Vector3f GetV2() const{return m_v2;}
        inline Vector3f GetV3() const{return m_v3;}
        inline Vector3f GetV4() const{return m_v4;}
        inline Vector3f GetV5() const{return m_v5;}
        inline Vector3f GetV6() const{return m_v6;}
        inline Vector3f GetV7() const{return m_v7;}
    protected:

    private:
        float m_w;
        Vector3f m_v0,m_v1,m_v2,m_v3,m_v4,m_v5,m_v6,m_v7;
};

#endif // CUBE_ENTITY_H
