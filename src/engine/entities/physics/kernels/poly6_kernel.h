#ifndef POLY6_KERNEL_H
#define POLY6_KERNEL_H

#include "engine/entities/physics/kernels/kernel.h"


class Poly6Kernel : public Kernel
{
    public:
        Poly6Kernel();
        virtual ~Poly6Kernel();
        float Evaluate(int,int,const Vector3f&,const Vector3f&, float) const;
        float EvaluateDerivative(int,int,int,const Vector3f&, const Vector3f&,float) const;
    protected:

    private:
        float m_k;
};

#endif // POLY6_KERNEL_H
