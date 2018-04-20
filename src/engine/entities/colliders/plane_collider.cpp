#include "engine/entities/colliders/plane_collider.h"
#include "engine/entities/geometry/plane_entity.h"

PlaneCollider::PlaneCollider(GeomEntity * geom_entity):ColliderEntity(geom_entity)
{
    //ctor
}

PlaneCollider::~PlaneCollider()
{
    //dtor
}

Collision PlaneCollider::GetCollision(const Vector3f& p) const{
    PlaneEntity * plane = (PlaneEntity *)m_geom_entity;
    float value = plane->EvaluatePoint(p);
    bool is_collision = (value <=0) && (plane->PointInPlane(p));
    return Collision(plane->GetNormal(),value,is_collision);
}

