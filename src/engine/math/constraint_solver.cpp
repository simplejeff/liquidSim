#include "constraint_solver.h"
#include <iostream>
#include  <cmath>

ConstraintSolver::ConstraintSolver(float epsilon,Kernel const * value_kernel,Kernel const * grad_kernel,Grid * grid,float rest_density):
m_epsilon(epsilon),m_value_kernel(value_kernel),m_grad_kernel(grad_kernel),m_grid(grid),m_rest_density(rest_density)
{
    //ctor
    m_k = .1;
    m_n = 4;
}

ConstraintSolver::~ConstraintSolver()
{
    //dtor
}

void ConstraintSolver::SolverIterations(size_t num_iterations,std::vector<Constraint *> & constraints,VectorXf & x){
    std::vector<Vector3f> new_x = ConvertPositions(x);
    m_neighbors = m_grid->getNN(new_x);
    for(size_t i = 0 ; i < num_iterations; i++){
            std::cout << "ITER: " << i << std::endl;
        SolverIter(constraints,x);
    }
}

void ConstraintSolver::SolverIter(std::vector<Constraint *> & constraints,VectorXf & x){
    //Compute lambda
    VectorXf lambda = ComputeLambda(m_neighbors,constraints,x);

    //Compute dp_i and do collision resolution (need to figure out what we want here)
    VectorXf Dp = ComputeDp(m_neighbors,x,lambda);

    x += Dp;
}


VectorXf ConstraintSolver::ComputeLambda(const std::vector<std::vector<int>> & neighbors,std::vector<Constraint *> & constraints,const VectorXf & x) const{
    VectorXf lambda(x.rows()/3,1);
    Constraint * constraint;
    float total = 0;
    for(size_t i = 0; i < constraints.size(); i++){
        constraint = constraints[i];
        std::vector<int> neighbors_i = neighbors[i];
        float C_i = constraint->Evaluate(neighbors_i,x);
        total +=C_i;
        VectorXf grad_C_i = constraint->GradEvaluate(neighbors_i,x);
        lambda(i) = -C_i / (grad_C_i.squaredNorm() + m_epsilon);
    }
    std::cout << total << std::endl;
    return lambda;
}

std::vector<Vector3f> ConstraintSolver::ConvertPositions(const VectorXf & x){
    std::vector<Vector3f> new_x;
    for(size_t i = 0; i < x.rows(); i+=3){
        new_x.push_back(Vector3f(x(i),x(i+1),x(i+2)));
    }
    return new_x;
}

VectorXf ConstraintSolver::ComputeDp(const std::vector<std::vector<int>> & neighbors,const VectorXf & x,const VectorXf & lambda){
    VectorXf dp(lambda.rows()*3,1);
    for(size_t i = 0; i < lambda.rows();i++){
        std::vector<int> neighbors_i = neighbors[i];
        Vector3f dp_i = ComputeDpAtIndex(neighbors_i,x,lambda,i);
        size_t tri_i = 3*i;
        dp(tri_i) = dp_i(0);
        dp(tri_i + 1) = dp_i(1);
        dp(tri_i + 2) = dp_i(2);
    }
    return dp/m_rest_density;
}

Vector3f ConstraintSolver::ComputeDpAtIndex(const std::vector<int> & neighbors_i,const VectorXf & x,const VectorXf & lambda,size_t i){
    //Have to make an assumption that the constraints are density constraints here...
    float lambda_i = lambda(i);
    Vector3f dp_i(0,0,0);
    size_t tri_i = 3*i;
    Vector3f p_i(x(tri_i),x(tri_i + 1),x(tri_i + 2));
    for(size_t l = 0; l < neighbors_i.size();l++){
        size_t j = neighbors_i[l];
        float lambda_j = lambda(j);
        size_t tri_j = 3*j;
        Vector3f p_j(x(tri_j),x(tri_j + 1),x(tri_j + 2));
        float W_top = m_value_kernel->Evaluate(p_i,p_j);
        Vector3f dq(.01*m_value_kernel->GetH(),0,0); //Paper suggest that |dq|= .1*h,...,.3*h
        float W_bot = m_value_kernel->Evaluate(dq,Vector3f(0,0,0));
        float s_corr = -m_k*std::pow(W_top/W_bot,m_n);
        //Tensile instability added here as well
        //dp_i += ((lambda_i + lambda_j + s_corr)*m_grad_kernel->GradEvaluate(i,j,i,p_i,p_j));
        dp_i += ((lambda_i + lambda_j)*m_grad_kernel->GradEvaluate(i,j,i,p_i,p_j));
    }
    return dp_i;
}

