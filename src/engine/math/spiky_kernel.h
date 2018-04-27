#ifndef SPIKY_KERNEL_H
#define SPIKY_KERNEL_H

#include  "src/engine/math/kernel.h"


class SpikyKernel : public Kernel
{
    public:
        SpikyKernel(float);
        virtual ~SpikyKernel();
        float Evaluate(const Vector3f&,const Vector3f &) const;
        Vector3f GradEvaluate(int,int,int,const Vector3f&,const Vector3f&) const;
    protected:

    private:
};

#endif // SPIKY_KERNEL_H
