#include "poly6_kernel.h"
#include <math.h>
#include <cmath>

Poly6Kernel::Poly6Kernel()
{
    //ctor
    m_k = 315.0/(64.0*M_PI);
}

Poly6Kernel::~Poly6Kernel()
{
    //dtor
}

float Poly6Kernel::Evaluate(int i,int j,const Vector3f& p_i,const Vector3f& p_j, float h) const{
    Vector3f dx = p_i - p_j;
    float r2 = dx.squaredNorm();
    if((r2 >=0) && (r2 <= h*h)){
        return ((m_k)/(std::pow(h,9)))*std::pow((h*h - r2),3);
    }
    return 0;
}

float Poly6Kernel::EvaluateDerivative(int i,int j,int k,const Vector3f& p_i, const Vector3f& p_j,float h) const{ //3rd index is the var that we are taking the derivative wrt
    Vector3f dx = p_i - p_j;
    float r2 = dx.squaredNorm();
    float r = sqrt(r2);
    if((r2 >=0) && (r2 <= h*h)){
        float t = 0;
        //return deriv
        if(k == i){ t = 1;}
        else if(k == j){ t = -1;}

        return 6*(m_k/std::pow(h,9))*std::pow(h*h-r2,2)*r*t;
    }
    return 0;
}
