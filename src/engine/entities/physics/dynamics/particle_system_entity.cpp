#include "engine/entities/physics/dynamics/particle_system_entity.h"

#include "engine/entities/colliders/sphere_collider.h"
#include <GL/freeglut.h>
#include <iostream>

ParticleSystemEntity::ParticleSystemEntity(ColliderEntity * collider_entity,const VectorXf & m,const VectorXf & q):
DynamicPhysicsEntity(collider_entity,m,q)
{
    //ctor
}

void ParticleSystemEntity::HandleCollision(const PhysicsEntity & entity){
    for(size_t i = 0;i< GetDim();i++){
       Collision collision = GetCollision(GetPosition(i),entity);
       ResolveCollision(i,collision);
    }
}

Collision ParticleSystemEntity::GetCollision(const Vector3f& p,const PhysicsEntity & entity) const{
    const ColliderEntity * collider = entity.GetColliderEntity();
    Collision collision = collider->GetCollision(p);
    collision.SetCoefficientRestitution(GetCoefficientRestitution(),entity.GetCoefficientRestitution());
    collision.SetCoefficientFriction(GetCoefficientFriction(),entity.GetCoefficientFriction());
    return collision;
}


void ParticleSystemEntity::ResolveCollision(size_t index,const Collision & collision){
    if(collision.IsCollision()){
        Vector3f n = collision.GetNormal();
        Vector3f v = GetVelocity(index);
        Vector3f v_n = v.dot(n)*n;
        Vector3f v_t = v - v_n;
        float dist = collision.GetCollisionDistance();
        if(fabs(dist) <= .1){
            Vector3f f = GetForce(index);

            if(fabs(v.dot(n)) < .5){ //Contact
                Vector3f f_n = f.dot(n)*n;
                SetForce(index,Vector3f(0,0,0));
                float friction_frac = -collision.GetCoefficientFriction();
                SetVelocity(index,v_t*friction_frac+v_n);
            }else{
                SetVelocity(index,v_t - collision.GetCoefficientRestitution()*v_n);
            }
        }
        if(dist < 0){
            SetPosition(index,GetPosition(index) + n*-dist);
        }
    }
}





ParticleSystemEntity::~ParticleSystemEntity()
{
    //dtor
}


