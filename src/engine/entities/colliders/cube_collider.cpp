#include "cube_collider.h"

CubeCollider::CubeCollider()
{
    //ctor
}

CubeCollider::~CubeCollider()
{
    //dtor
}


//std::vector<int> CubeCollider::GetCollision(const Vector3f& p) const{
//    return std::vector<int>();
//    CubeEntity * m_cube_entity = (CubeEntity *)m_geom_entity;
/*    TransformEntity default_transform;
    PlaneEntity plane0(&default_transform,m_cube_entity->GetV0(),m_cube_entity->GetV1(),m_cube_entity->GetV3(),m_cube_entity->GetV2());
    PlaneEntity plane1(&default_transform,m_cube_entity->GetV0(),m_cube_entity->GetV7(),m_cube_entity->GetV4(),m_cube_entity->GetV1());
    PlaneEntity plane2(&default_transform,m_cube_entity->GetV1(),m_cube_entity->GetV4(),m_cube_entity->GetV5(),m_cube_entity->GetV3());
    PlaneEntity plane3(&default_transform,m_cube_entity->GetV3(),m_cube_entity->GetV5(),m_cube_entity->GetV6(),m_cube_entity->GetV2());
    PlaneEntity plane4(&default_transform,m_cube_entity->GetV2(),m_cube_entity->GetV6(),m_cube_entity->GetV7(),m_cube_entity->GetV0());
    PlaneEntity plane5(&default_transform,m_cube_entity->GetV7(),m_cube_entity->GetV6(),m_cube_entity->GetV5(),m_cube_entity->GetV4());

    PlaneCollider collider(&plane0);
    Collision collision = (collider.GetCollision(p)).at(0);
    bool isCollision = false;
    std::vector<Collision> collisions;
    if(collision.IsCollision()){
        isCollision = true;
        collisions.push_back(collision);}
    collider.SetGeomEntity(&plane1);
    Collision collision1 = (collider.GetCollision(p)).at(0);
    if(collision1.IsCollision()){
        isCollision = true;

        collisions.push_back(collision1);}
    //Add all other faces
    collider.SetGeomEntity(&plane2);
    Collision collision2 = (collider.GetCollision(p)).at(0);
    if(collision2.IsCollision()){
        isCollision = true;
        collisions.push_back(collision2);}
    collider.SetGeomEntity(&plane3);
    Collision collision3 = (collider.GetCollision(p)).at(0);
    if(collision3.IsCollision()){
        isCollision = true;
        collisions.push_back(collision3);}
    collider.SetGeomEntity(&plane4);
    Collision collision4 = (collider.GetCollision(p)).at(0);
    if(collision4.IsCollision()){
        isCollision = true;
        collisions.push_back(collision4);}
    collider.SetGeomEntity(&plane5);
    Collision collision5 = (collider.GetCollision(p)).at(0);
    if(collision5.IsCollision()){
        isCollision = true;
        collisions.push_back(collision5);}
    return collisions;
     /*   Vector3f norm = Vector3f(0.f, 0.f, 0.f);
        float dist = 0.f;
        for(Collision c : collisions) {
            if(c.IsCollision()) {
                norm = norm + c.GetNormal()*c.GetCollisionDistance();
                dist = dist + c.GetCollisionDistance();
            }
        }
        //float dist = norm.norm();
        norm = norm.normalized();
        return Collision(norm, dist, isCollision);
    } else {
        collisions.push_back(Collision());
    }*/
//}
