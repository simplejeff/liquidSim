#ifndef KERNEL_H
#define KERNEL_H

#include <math.h>
#include <cmath>
#include <Eigen/Dense>
using namespace Eigen;

class Kernel
{
    public:
        Kernel(float);
        virtual ~Kernel();
        virtual float Evaluate(const Vector3f&,const Vector3f &) const = 0;
        virtual Vector3f GradEvaluate(int,int,int,const Vector3f&,const Vector3f&) const = 0;
        inline float GetH() const{return m_h;}
    protected:
        float m_h;
        Vector3f Delta(int,int,int,const Vector3f &,const Vector3f &) const;
    private:
};


#endif // KERNEL_H
