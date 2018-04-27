#include "poly6_kernel.h"

Poly6Kernel::Poly6Kernel(float h):Kernel(h)
{
    //ctor
}

Poly6Kernel::~Poly6Kernel()
{
    //dtor
}

float Poly6Kernel::Evaluate(const Vector3f& p_i,const Vector3f & p_j) const{
    float r2 = (p_i - p_j).squaredNorm();
    if((r2 >= 0) && (r2 <= m_h*m_h)){
        return (315.0/(64.0*M_PI*std::pow(m_h,9)))*std::pow(m_h*m_h - r2,3);
    }
    return 0;
}

Vector3f Poly6Kernel::GradEvaluate(int i,int j,int k,const Vector3f& p_i,const Vector3f& p_j) const{
    float r2 = (p_i - p_j).squaredNorm();
    if((r2 >= 0) && (r2 <= m_h*m_h)){
        return (-945.0/(32.0*M_PI*std::pow(m_h,9)))*std::pow(m_h*m_h-r2,2)*Delta(i,j,k,p_i,p_j);
    }
    return Vector3f(0,0,0);
}
