#ifndef CONSTRAINT_SOLVER_H
#define CONSTRAINT_SOLVER_H

#include "src/engine/physics/constraint.h"
#include  "src/engine/math/grid.h"
#include  "src/engine/math/kernel.h"
#include <vector>

class ConstraintSolver
{
    public:
        ConstraintSolver(float,Kernel const *,Kernel const *,Grid *,float);
        virtual ~ConstraintSolver();
        void SolverIterations(size_t,std::vector<Constraint *> & ,VectorXf &); //Note it actually changes the positions
    protected:

    private:
        void SolverIter(std::vector<Constraint *> & ,VectorXf &);
        VectorXf ComputeLambda(const std::vector<std::vector<int>> &,std::vector<Constraint *> &,const VectorXf &) const;
        std::vector<Vector3f> ConvertPositions(const VectorXf &);
        VectorXf ComputeDp(const std::vector<std::vector<int>> &,const VectorXf &,const VectorXf &);
        Vector3f ComputeDpAtIndex(const std::vector<int> &,const VectorXf &,const VectorXf &,size_t);
        float m_epsilon;
        Kernel const * m_value_kernel;
        Kernel const * m_grad_kernel;
        Grid * m_grid;
        std::vector<std::vector<int>> m_neighbors;
        float m_rest_density;
        float m_k;
        size_t m_n;
};

#endif // CONSTRAINT_SOLVER_H
