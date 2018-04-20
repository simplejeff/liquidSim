#include "engine/entities/colliders/sphere_collider.h"
#include <stdlib.h>

SphereCollider::SphereCollider(Sphere * geom_entity):ColliderEntity(geom_entity)
{
    //ctor
}


Collision SphereCollider::GetCollision(const ColliderEntity & entity) const{
    return Collision();
}


Collision SphereCollider::GetCollision(const SphereCollider & entity) const{
    /*SphereEntity * sphere_A = (SphereEntity *)m_geom_entity;
    SphereEntity * sphere_B = (SphereEntity *)entity.GetGeomEntity();
    Vector3f translate_A = m_transform_entity->GetTranslate();
    Vector3f translate_B = entity.GetTransformEntity()->GetTranslate();
    Vector3f center_A = sphere_A->GetCenter() + translate_A;
    Vector3f center_B = sphere_B->GetCenter() + translate_B;
    float radius_A = sphere_A->GetRadius();
    float radius_B = sphere_B->GetRadius();
    Vector3f AB = center_B - center_A;
    Vector3f BA = -AB;
    bool is_collision = (( ( AB.dot(AB) ) - ( radius_A*radius_A +2.0*radius_A*radius_B + radius_B*radius_B ) ) <= 0);
    if(is_collision){
        return Collision(BA.normalized(),AB.normalized(),AB.norm(),is_collision);
    }else{
        return Collision();
    }*/
}

Collision SphereCollider::GetCollision(const PlaneCollider & entity) const{
    /*SphereEntity * sphere_A = (SphereEntity *)m_geom_entity;
    PlaneEntity * plane_B = (PlaneEntity *)entity.GetGeomEntity();
    Vector3f translate_A = m_transform_entity->GetTranslate();
    Vector3f translate_B = entity.GetTransformEntity()->GetTranslate();
    Vector3f center_A = sphere_A->GetCenter() + translate_A;
    float radius_A = sphere_A->GetRadius();
    Vector3f normal_B = plane_B->GetNormal();
    Vector3f top_A = center_A + radius_A*normal_B;
    Vector3f bot_A = center_A - radius_A*normal_B;
    bool proj_in_plane = plane_B->ProjectedPointInPlane(center_A - translate_B); //Accounts for transform of plane_B
    if(proj_in_plane){
        float top_A_eval = plane_B->EvaluatePoint(top_A);
        float bot_A_eval = plane_B->EvaluatePoint(bot_A);
        bool chopped = ((top_A_eval > 0) && (bot_A_eval < 0));
        bool under = ((top_A_eval <= 0) && (bot_A_eval <= 0));
        float dist = plane_B->EvaluatePoint(center_A);
        if(chopped){
            bool center_above = (dist > 0);
            if(center_above){
                return Collision(normal_B,-normal_B,radius_A - fabs(dist),true);
            }else{
                return Collision(normal_B,-normal_B,radius_A + fabs(dist),true);
            }
        }else if(under){
            return Collision(normal_B,-normal_B,radius_A + fabs(dist),true);
        }
    }
    return Collision();*/
}



SphereCollider::~SphereCollider()
{
    //dtor
}
