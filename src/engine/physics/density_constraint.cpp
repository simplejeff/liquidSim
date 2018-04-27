#include "density_constraint.h"
#include <iostream>

DensityConstraint::DensityConstraint(size_t id,float rest_density,Kernel const * value_kernel,Kernel const * grad_kernel):
Constraint(id),m_rest_density(rest_density),m_value_kernel(value_kernel),m_grad_kernel(grad_kernel)
{
    //ctor
}

DensityConstraint::~DensityConstraint()
{
    //dtor
}

float DensityConstraint::Evaluate(const std::vector<int> & indices,const VectorXf & x) const{
    return (ComputeDensity(indices,x)/m_rest_density) - 1.0;
}

VectorXf DensityConstraint::GradEvaluate(const std::vector<int> & indices,const VectorXf & x) const{
    return ComputeDensityGradient(indices,x)/m_rest_density;
}

float DensityConstraint::ComputeDensity(const std::vector<int> & indices,const VectorXf & x) const{
    float density_i = 0;
    size_t tri_i = 3*m_id;
    Vector3f p_i(x(tri_i),x(tri_i + 1),x(tri_i + 2));
    for(size_t l = 0; l < indices.size();l++){
        size_t j = indices[l];
        size_t tri_j = 3*j;
        Vector3f p_j(x(tri_j),x(tri_j + 1),x(tri_j + 2));
        density_i += m_value_kernel->Evaluate(p_i,p_j);
    }
    return density_i;
}


VectorXf DensityConstraint::ComputeDensityGradient(const std::vector<int> & indices,const VectorXf & x) const{
    VectorXf grad_i(3*indices.size(),1);
    for(size_t l = 0; l < indices.size(); l++){
        size_t k = indices[l];
        size_t tri_l = 3*l;
        Vector3f density_i_grad_k = ComputeDensityGradientAtIndex(indices,x,k);
        grad_i(tri_l) = density_i_grad_k(0);
        grad_i(tri_l + 1) = density_i_grad_k(1);
        grad_i(tri_l + 2) = density_i_grad_k(2);
    }
    return grad_i;
}

Vector3f DensityConstraint::ComputeDensityGradientAtIndex(const std::vector<int> & indices,const VectorXf & x,int k) const{
    Vector3f density_i_grad_k(0,0,0);
    size_t tri_i = 3*m_id;
    Vector3f p_i(x(tri_i),x(tri_i + 1),x(tri_i + 2));
    if(k == m_id){ //If we are taking the grad wrt i aka m_id
        for(size_t l = 0; l < indices.size();l++){
            size_t j = indices[l];
            size_t tri_j = 3*j;
            Vector3f p_j(x(tri_j),x(tri_j + 1),x(tri_j + 2));
            density_i_grad_k += m_grad_kernel->GradEvaluate(m_id,j,k,p_i,p_j);
        }
        return density_i_grad_k;
    }
    //Otherwise we must be taking it wrt to one of the j neq i in the neighbor list (means k = j)
    size_t tri_k = 3*k;
    Vector3f p_k(x(tri_k),x(tri_k + 1),x(tri_k + 2));
    density_i_grad_k += m_grad_kernel->GradEvaluate(m_id,k,k,p_i,p_k);
    return density_i_grad_k;
}

