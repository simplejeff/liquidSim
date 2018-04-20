#ifndef KERNEL_H
#define KERNEL_H

#include "engine/entities/entity.h"
#include <Eigen/Core>
using namespace Eigen;

class Kernel : public Entity
{
    public:
        Kernel();
        virtual ~Kernel();
        virtual float Evaluate(int,int,const Vector3f&,const Vector3f&, float) const= 0;
        virtual float EvaluateDerivative(int,int,int,const Vector3f&, const Vector3f&,float) const = 0;
    protected:

    private:
};

#endif // KERNEL_H
