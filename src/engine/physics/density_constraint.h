#ifndef DENSITY_CONSTRAINT_H
#define DENSITY_CONSTRAINT_H

#include  "src/engine/physics/constraint.h"
#include  "src/engine/math/kernel.h"

class DensityConstraint : public Constraint
{
    public:
        DensityConstraint(size_t,float,Kernel const *,Kernel const *);
        virtual ~DensityConstraint();
        float Evaluate(const std::vector<int> &,const VectorXf &) const;
        VectorXf GradEvaluate(const std::vector<int> &,const VectorXf &) const;
    protected:

    private:
        float ComputeDensity(const std::vector<int> &,const VectorXf &) const;
        VectorXf ComputeDensityGradient(const std::vector<int> &,const VectorXf &) const;
        Vector3f ComputeDensityGradientAtIndex(const std::vector<int> &,const VectorXf &,int) const;
        float m_rest_density;
        Kernel const * m_value_kernel;
        Kernel const * m_grad_kernel;
};

#endif // DENSITY_CONSTRAINT_H
