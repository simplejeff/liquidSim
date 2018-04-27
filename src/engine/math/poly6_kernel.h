#ifndef POLY6_KERNEL_H
#define POLY6_KERNEL_H

#include  "src/engine/math/kernel.h"


class Poly6Kernel : public Kernel
{
    public:
        Poly6Kernel(float);
        virtual ~Poly6Kernel();
        float Evaluate(const Vector3f&,const Vector3f &) const;
        Vector3f GradEvaluate(int,int,int,const Vector3f&,const Vector3f&) const;
    protected:

    private:
};

#endif // POLY6_KERNEL_H
