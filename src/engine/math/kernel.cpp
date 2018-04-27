#include "kernel.h"

Kernel::Kernel(float h):m_h(h)
{
    //ctor
}

Kernel::~Kernel()
{
    //dtor
}

Vector3f Kernel::Delta(int i,int j,int k,const Vector3f & p_i,const Vector3f & p_j) const{
    Vector3f r_unit = (p_i - p_j).normalized();
    if(k == i){ return r_unit;}
    if(k == j){ return -r_unit;}
    return Vector3f(0,0,0);
}
