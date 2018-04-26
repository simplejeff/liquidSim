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
       std::vector<Collision> collisions = GetCollision(GetPosition(i),entity);
       ResolveCollision(i,collisions);
    }
}

std::vector<Collision> ParticleSystemEntity::GetCollision(const Vector3f& p,const PhysicsEntity & entity) const{
    const ColliderEntity * collider = entity.GetColliderEntity();
    std::vector<Collision> collisions = collider->GetCollision(p);
    for(int i = 0; i < collisions.size(); i++) {
        Collision collision = collisions.at(i);
        collision.SetCoefficientRestitution(GetCoefficientRestitution(),entity.GetCoefficientRestitution());
        collision.SetCoefficientFriction(GetCoefficientFriction(),entity.GetCoefficientFriction());
        collisions.at(i) = collision;
    }
    //collision.SetCoefficientRestitution(GetCoefficientRestitution(),entity.GetCoefficientRestitution());
    //collision.SetCoefficientFriction(GetCoefficientFriction(),entity.GetCoefficientFriction());
    return collisions;
}


void ParticleSystemEntity::ResolveCollision(size_t index,const std::vector<Collision> & collisions){
    for(Collision collision : collisions) {
        if(collision.IsCollision()){
            Vector3f n = collision.GetNormal();
            Vector3f v = GetVelocity(index);
            Vector3f v_n = v.dot(n)*n;
            Vector3f v_t = v - v_n;
            Vector3f p = GetPosition(index);
            float dist = collision.GetCollisionDistance();
            if(fabs(dist) <= .15){
                Vector3f f = GetForce(index);
                Vector3f newVelocity;
                if(fabs((v.normalized()).dot(n)) < .6){ //Contact
                    Vector3f f_n = f.dot(n)*n;
                    SetForce(index,Vector3f(0,0,0));
                    float friction_frac = -collision.GetCoefficientFriction();
                    //SetVelocity(index,v_t*friction_frac+v_n);
                    newVelocity = v_t*collision.GetCoefficientFriction();
                }else{
                    newVelocity = v_t;
                }
                std::cout << "restitution : " << collision.GetCoefficientRestitution() << std::endl;
                SetVelocity(index, newVelocity - collision.GetCoefficientRestitution()*v_n);
                //SetVelocity(index,v_t - collision.GetCoefficientRestitution()*v_n);
            }
              if(dist <= 0.f){
                    SetPosition(index,GetPosition(index) + n*(.0001f - dist));
              }
        }
    }
}





ParticleSystemEntity::~ParticleSystemEntity()
{
    //dtor
}


