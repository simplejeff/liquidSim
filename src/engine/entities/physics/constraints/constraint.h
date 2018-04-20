#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include "engine/entities/entity.h"
#include <Eigen/Core>
using namespace Eigen;

class Constraint : public Entity
{
    public:
        Constraint();
        virtual ~Constraint();
        virtual float Evaluate(const VectorXf &) const = 0;
        virtual float EvaluateDerivative(const VectorXf &) const = 0;
    protected:

    private:
};

#endif // CONSTRAINT_H
