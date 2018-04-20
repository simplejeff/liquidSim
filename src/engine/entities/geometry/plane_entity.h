#ifndef PLANEENTITY_H
#define PLANEENTITY_H

#include "engine/entities/geometry/geom_entity.h"
#include <Eigen/Dense>

using namespace Eigen;

class PlaneEntity : public GeomEntity
{
    public:
        PlaneEntity(TransformEntity *,const Vector3f &,const Vector3f&,const Vector3f&,const Vector3f&);
        virtual ~PlaneEntity();
        inline Vector3f GetNormal() const{return m_normal;}
        inline float EvaluatePoint(const Vector3f& p) const{ return m_normal.dot(p - m_v0);}
        Vector3f GetProjectedPointInPlane(const Vector3f &) const;
        bool ProjectedPointInPlane(const Vector3f) const;
        bool PointInPlane(const Vector3f &) const;
        inline Vector3f GetV0() const{return m_v0;}
        inline Vector3f GetV1() const{return m_v1;}
        inline Vector3f GetV2() const{return m_v2;}
        inline Vector3f GetV3() const{return m_v3;}
    protected:

    private:
        bool PointInTriangle(const Vector3f &,const Vector3f &,const Vector3f &,const Vector3f &) const;
        Vector3f m_v0,m_v1,m_v2,m_v3;
        Vector3f m_normal;
};

#endif // PLANEENTITY_H
