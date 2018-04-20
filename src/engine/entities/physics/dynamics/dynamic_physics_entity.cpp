#include "engine/entities/physics/dynamics/dynamic_physics_entity.h"
#include <iostream>

DynamicPhysicsEntity::DynamicPhysicsEntity(ColliderEntity * collider,const VectorXf & m,const VectorXf & q):PhysicsEntity(collider),m_m(m),m_q(q)
{
    //ctor
    m_f = VectorXf(m_m.rows()*3);
    m_q_dt = m_q;
    VectorXf m_temp(m_m.rows()*3);
    for(size_t i = 0;i<m_m.size();i++){
        size_t index = 3*i;
        m_temp(index) = m_m(i);
        m_temp(index+1) = m_m(i);
        m_temp(index+2) = m_m(i);
    }
    m_M_inv = m_temp.asDiagonal().inverse();
    m_physics_entity_type = DYNAMIC;
}


DynamicPhysicsEntity::~DynamicPhysicsEntity()
{
    //dtor
}


void DynamicPhysicsEntity::ClearForces(){
    m_f = MatrixXf::Zero(m_f.rows(),1);
}


void DynamicPhysicsEntity::AddForce(const VectorXf & f){
    m_f+=f;
}

VectorXf DynamicPhysicsEntity::GetPositions() const{
    return m_q.head(m_m.rows()*3);
}

VectorXf DynamicPhysicsEntity::GetVelocities() const{
    return m_q.tail(m_m.rows()*3);
}

const VectorXf & DynamicPhysicsEntity::GetState() const{
    return m_q;
}

const VectorXf & DynamicPhysicsEntity::GetDerivativeState() const{
    return m_q_dt;
}

void DynamicPhysicsEntity::SetState(const VectorXf & q){
    m_q = q;
}

void DynamicPhysicsEntity::SetPositions(const VectorXf & p){
    m_q.head(m_m.rows()) = p;
}

void DynamicPhysicsEntity::SetVelocities(const VectorXf & v){
    m_q.tail(m_m.rows()) = v;
}

Vector3f DynamicPhysicsEntity::GetPosition(int index) const{
    int new_index = 3*index;
    return Vector3f(m_q(new_index),m_q(new_index + 1),m_q(new_index + 2));
}

Vector3f DynamicPhysicsEntity::GetVelocity(int index) const{
    int new_index = 3*(index + m_m.size());
    return Vector3f(m_q(new_index),m_q(new_index + 1),m_q(new_index + 2));
}

Vector3f DynamicPhysicsEntity::GetForce(int index) const{
    int new_index = 3*index;
    return Vector3f(m_f(index),m_f(index+1),m_f(index+2));
}


void DynamicPhysicsEntity::SetPosition(int index,const Vector3f & p){
    int new_index = 3*index;
    m_q(new_index) = p(0);
    m_q(new_index + 1) = p(1);
    m_q(new_index + 2) = p(2);
}

void DynamicPhysicsEntity::SetVelocity(int index,const Vector3f & v){
    int new_index = 3*(index +m_m.size());
    m_q(new_index) = v(0);
    m_q(new_index + 1) = v(1);
    m_q(new_index + 2) = v(2);
}

void DynamicPhysicsEntity::SetForce(int index,const Vector3f &f){
    int new_index = 3*index;
    m_f(new_index) = f(0);
    m_f(new_index + 1) = f(1);
    m_f(new_index + 2) = f(2);
}

void DynamicPhysicsEntity::ComputeStateDerivative(){
    m_q_dt << GetVelocities(), m_M_inv*m_f;
}


