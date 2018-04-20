#include "cube_entity.h"

CubeEntity::CubeEntity(TransformEntity * transform_entity,const float width, const Vector3f & v0,const Vector3f& v1,const Vector3f& v2):GeomEntity(transform_entity),m_v0(v0),m_v1(v1),m_v2(v2)
{
    //ctor
    Vector3f v01 = m_v1 - m_v0;
    Vector3f v02 = m_v2 - m_v0;
    Vector3f v07 = v01.cross(v02).normalized()*v02.norm();
    m_v3 = m_v0 + v01 + v02;
    m_v4 = m_v0 + v01 + v07;
    m_v5 = m_v3 + v07;
    m_v6 = m_v2 + v07;
    m_v7 = m_v0 + v07;
    m_w = width;
}

CubeEntity::~CubeEntity()
{
    //dtor
}
