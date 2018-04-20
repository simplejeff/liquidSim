#ifndef DYNAMICPHYSICSENTITY_H
#define DYNAMICPHYSICSENTITY_H

#include "engine/entities/physics/physics_entity.h"


class DynamicPhysicsEntity : public PhysicsEntity
{
    public:
        DynamicPhysicsEntity(ColliderEntity *,const VectorXf &,const VectorXf &);
        virtual ~DynamicPhysicsEntity();
        virtual void HandleCollision(const PhysicsEntity &) = 0;
        void ClearForces();
        void AddForce(const VectorXf &);
        inline size_t GetDim() const{ return m_m.rows();}
        VectorXf GetPositions() const;
        VectorXf GetVelocities() const;
        Vector3f GetPosition(int) const;
        Vector3f GetVelocity(int) const;
        Vector3f GetForce(int) const;
        void SetPosition(int,const Vector3f &);
        void SetVelocity(int,const Vector3f &);
        void SetForce(int,const Vector3f &);
        const VectorXf & GetState() const;
        const VectorXf & GetDerivativeState() const;
        void SetState(const VectorXf &);
        void SetPositions(const VectorXf &);
        void SetVelocities(const VectorXf &);
        void ComputeStateDerivative();
    protected:
        VectorXf m_m; //Mass of each physics entity
        VectorXf m_q; //State of phyics entity: positions and velocities
        VectorXf m_q_dt; //Derivative of the state vector
        MatrixXf m_M_inv;
        VectorXf m_f; //Forces on each entity
        //Add constraints here whenever we write these
    private:
};

#endif // DYNAMICPHYSICSENTITY_H
