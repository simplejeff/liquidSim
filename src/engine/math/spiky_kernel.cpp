#include "spiky_kernel.h"

SpikyKernel::SpikyKernel(float h):Kernel(h)
{
    //ctor
}

SpikyKernel::~SpikyKernel()
{
    //dtor
}

float SpikyKernel::Evaluate(const Vector3f& p_i,const Vector3f & p_j) const{
    float r = (p_i - p_j).norm();
    float r2 = r*r;
    if((r2 >=0) && (r2 <= m_h*m_h)){
        return (15.0/(M_PI*std::pow(m_h,6)))*std::pow(m_h - r,3);
    }
    return 0;
}

Vector3f SpikyKernel::GradEvaluate(int i,int j,int k,const Vector3f& p_i,const Vector3f& p_j) const{
    float r = (p_i - p_j).norm();
    float r2 = r*r;
    if((r2 >= 0) && (r2 <= m_h*m_h)){
        return (-45.0/(M_PI*std::pow(m_h,6)))*std::pow(m_h - r,2)*Delta(i,j,k,p_i,p_j);
    }
    return Vector3f(0,0,0);
}
