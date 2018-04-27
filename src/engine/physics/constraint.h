#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include <Eigen/Dense>
using namespace Eigen;

class Constraint
{
    public:
        Constraint(size_t);
        virtual ~Constraint();
        virtual float Evaluate(const std::vector<int> &,const VectorXf &) const = 0;
        virtual VectorXf GradEvaluate(const std::vector<int> &,const VectorXf &) const = 0;
    protected:
        size_t m_id;
    private:
};

#endif // CONSTRAINT_H
