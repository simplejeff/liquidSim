#include "cube_collider.h"
#include "engine/entities/geometry/plane_entity.h"
#include "engine/entities/geometry/cube_entity.h"
#include "plane_collider.h"

CubeCollider::CubeCollider(GeomEntity * geom_entity):ColliderEntity(geom_entity)
{
    //ctor
}

CubeCollider::~CubeCollider()
{
    //dtor
}


Collision CubeCollider::GetCollision(const Vector3f& p) const{
    CubeEntity * m_cube_entity = (CubeEntity *)m_geom_entity;
    TransformEntity default_transform;
    PlaneEntity plane0(&default_transform,m_cube_entity->GetV0(),m_cube_entity->GetV1(),m_cube_entity->GetV3(),m_cube_entity->GetV2());
    PlaneEntity plane1(&default_transform,m_cube_entity->GetV0(),m_cube_entity->GetV7(),m_cube_entity->GetV4(),m_cube_entity->GetV1());
    PlaneEntity plane2(&default_transform,m_cube_entity->GetV1(),m_cube_entity->GetV4(),m_cube_entity->GetV5(),m_cube_entity->GetV3());
    PlaneEntity plane3(&default_transform,m_cube_entity->GetV3(),m_cube_entity->GetV5(),m_cube_entity->GetV6(),m_cube_entity->GetV2());
    PlaneEntity plane4(&default_transform,m_cube_entity->GetV2(),m_cube_entity->GetV6(),m_cube_entity->GetV7(),m_cube_entity->GetV0());
    PlaneEntity plane5(&default_transform,m_cube_entity->GetV7(),m_cube_entity->GetV6(),m_cube_entity->GetV5(),m_cube_entity->GetV4());

    PlaneCollider collider(&plane0);
    Collision collision = collider.GetCollision(p);
    if(collision.IsCollision()){ return collision;}
    collider.SetGeomEntity(&plane1);
    collision = collider.GetCollision(p);
    if(collision.IsCollision()){ return collision;}
    //Add all other faces
    collider.SetGeomEntity(&plane2);
    collision = collider.GetCollision(p);
    if(collision.IsCollision()){ return collision;}
    collider.SetGeomEntity(&plane3);
    collision = collider.GetCollision(p);
    if(collision.IsCollision()){ return collision;}
    collider.SetGeomEntity(&plane4);
    collision = collider.GetCollision(p);
    if(collision.IsCollision()){ return collision;}
    collider.SetGeomEntity(&plane5);
    collision = collider.GetCollision(p);
    if(collision.IsCollision()){ return collision;}
    return Collision();
}
