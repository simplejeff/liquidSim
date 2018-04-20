#ifndef DENSITY_CONSTRAINT_H
#define DENSITY_CONSTRAINT_H

#include "engine/entities/physics/constraints/constraint.h"


class DensityConstraint : public Constraint
{
    public:
        DensityConstraint(float );
        virtual ~DensityConstraint();

    protected:

    private:
        float m_rest_density;
};

#endif // DENSITY_CONSTRAINT_H
