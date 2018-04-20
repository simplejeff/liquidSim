#include "engine/entities/geometry/plane_entity.h"

PlaneEntity::PlaneEntity(TransformEntity * transform_entity,const Vector3f & v0,const Vector3f& v1,const Vector3f& v2,const Vector3f& v3):GeomEntity(transform_entity),m_v0(v0),m_v1(v1),m_v2(v2),m_v3(v3)
{
    //ctor
    m_normal = (v1 - v0).cross(v2 - v0).normalized();
}

Vector3f PlaneEntity::GetProjectedPointInPlane(const Vector3f & p) const{
    Vector3f v = p - m_v0;
    Vector3f v_proj = v - v.dot(m_normal)*m_normal;
    return v_proj + m_v0;
}


bool PlaneEntity::ProjectedPointInPlane(const Vector3f p) const{
    return PointInPlane(GetProjectedPointInPlane(p));
}

bool PlaneEntity::PointInPlane(const Vector3f & p) const{
    return (PointInTriangle(p,m_v0,m_v1,m_v2) || PointInTriangle(p,m_v0,m_v2,m_v3));
}

bool PlaneEntity::PointInTriangle(const Vector3f & p,const Vector3f & a,const Vector3f & b,const Vector3f & c) const{
    float test_a = (b - a).cross(p-a).dot(m_normal);
    float test_b = (c - b).cross(p-b).dot(m_normal);
    float test_c = (a - c).cross(p-c).dot(m_normal);
    bool outer_orientation = ((test_a >=0) && (test_b >=0) && (test_c >=0));
    bool inner_orientation = ((test_a <0) && (test_b <0) && (test_c <0));
    return (outer_orientation || inner_orientation);
}




PlaneEntity::~PlaneEntity()
{
    //dtor
}
