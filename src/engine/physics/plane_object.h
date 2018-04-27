#ifndef PLANE_OBJECT_H
#define PLANE_OBJECT_H

#include  "src/engine/physics/static_object.h"
#include <Eigen/Dense>
using namespace Eigen;

class PlaneObject : public StaticObject
{
    public:
        PlaneObject(float,float,const VectorXf &);
        virtual ~PlaneObject();
        std::vector<Collision> GetCollision(const Vector3f &) const;
        void Render(Graphics *g) const;
    protected:

    private:
        float DistanceToPlane(const Vector3f &) const;
        Vector3f ProjectPoint(const Vector3f &) const;
        bool ProjectedPointInPlane(const Vector3f &) const;
        bool ProjectedPointInTriangle(const Vector3f &,const Vector3f &,const Vector3f&, const Vector3f&) const;
        VectorXf m_positions;
        Vector3f m_normal;
};

#endif // PLANE_OBJECT_H
