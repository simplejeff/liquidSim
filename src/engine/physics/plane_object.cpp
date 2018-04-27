#include "plane_object.h"
#include <iostream>
#include <GL/freeglut.h>

PlaneObject::PlaneObject(float friction_coeff,float restitution_coeff,const VectorXf & positions):StaticObject(friction_coeff,restitution_coeff),m_positions(positions)
{
    //ctor
    Vector3f v0(m_positions(0),m_positions(1),m_positions(2));
    Vector3f v1(m_positions(3),m_positions(4),m_positions(5));
    Vector3f v2(m_positions(6),m_positions(7),m_positions(8));
    Vector3f v3(m_positions(9),m_positions(10),m_positions(11));
    m_normal = (v1 - v0).cross(v2 - v0).normalized();
    Vector3f bot1 = v2;
    Vector3f bot2 = v1;
    Vector3f bot3 = v3;
    Vector3f bot4 = v0;
    Vector3f botnorm = m_normal;
    Vector2f texture = Vector2f(0.f, 0.f);
    std::vector<float> shapedata;
    shapedata.push_back(bot1[0]);
    shapedata.push_back(bot1[1]);
    shapedata.push_back(bot1[2]);
    shapedata.push_back(botnorm[0]);
    shapedata.push_back(botnorm[1]);
    shapedata.push_back(botnorm[2]);
    shapedata.push_back(texture[0]);
    shapedata.push_back(texture[1]);

    shapedata.push_back(bot3[0]);
    shapedata.push_back(bot3[1]);
    shapedata.push_back(bot3[2]);
    shapedata.push_back(botnorm[0]);
    shapedata.push_back(botnorm[1]);
    shapedata.push_back(botnorm[2]);
    shapedata.push_back(texture[0]);
    shapedata.push_back(texture[1]);

    shapedata.push_back(bot2[0]);
    shapedata.push_back(bot2[1]);
    shapedata.push_back(bot2[2]);
    shapedata.push_back(botnorm[0]);
    shapedata.push_back(botnorm[1]);
    shapedata.push_back(botnorm[2]);
    shapedata.push_back(texture[0]);
    shapedata.push_back(texture[1]);

    shapedata.push_back(bot2[0]);
    shapedata.push_back(bot2[1]);
    shapedata.push_back(bot2[2]);
    shapedata.push_back(botnorm[0]);
    shapedata.push_back(botnorm[1]);
    shapedata.push_back(botnorm[2]);
    shapedata.push_back(texture[0]);
    shapedata.push_back(texture[1]);

    shapedata.push_back(bot3[0]);
    shapedata.push_back(bot3[1]);
    shapedata.push_back(bot3[2]);
    shapedata.push_back(botnorm[0]);
    shapedata.push_back(botnorm[1]);
    shapedata.push_back(botnorm[2]);
    shapedata.push_back(texture[0]);
    shapedata.push_back(texture[1]);

    shapedata.push_back(bot4[0]);
    shapedata.push_back(bot4[1]);
    shapedata.push_back(bot4[2]);
    shapedata.push_back(botnorm[0]);
    shapedata.push_back(botnorm[1]);
    shapedata.push_back(botnorm[2]);
    shapedata.push_back(texture[0]);
    shapedata.push_back(texture[1]);
    m_shape = std::make_shared<Shape>(shapedata);
}

PlaneObject::~PlaneObject()
{
    //dtor
}

std::vector<Collision> PlaneObject::GetCollision(const Vector3f & p) const{
    std::vector<Collision> collisions;
    float distance = DistanceToPlane(p);
    bool valid = ((distance <= 0));// && (ProjectedPointInPlane(ProjectPoint(p))));
    collisions.push_back(Collision(m_normal,distance,valid,m_friction_coeff,m_restitution_coeff));
    return collisions;
}


void PlaneObject::Render(Graphics *g) const{
    g->setColor(glm::vec3(m_color[0],m_color[1],m_color[2]));
    m_shape->draw(g);
    g->clearTransform();
}

float PlaneObject::DistanceToPlane(const Vector3f & p) const{
    Vector3f v = p - Vector3f(m_positions(0),m_positions(1),m_positions(2));
    return v.dot(m_normal);
}


Vector3f PlaneObject::ProjectPoint(const Vector3f & p) const{
    Vector3f v = p - Vector3f(m_positions(0),m_positions(1),m_positions(2));
    Vector3f v_n = v.dot(m_normal)*m_normal;
    Vector3f v_t = v - v_n;
    return Vector3f(m_positions(0),m_positions(1),m_positions(2)) + v_t;
}

bool PlaneObject::ProjectedPointInPlane(const Vector3f & p) const{
    Vector3f v0(m_positions(0),m_positions(1),m_positions(2));
    Vector3f v1(m_positions(3),m_positions(4),m_positions(5));
    Vector3f v2(m_positions(6),m_positions(7),m_positions(8));
    Vector3f v3(m_positions(9),m_positions(10),m_positions(11));
    return (ProjectedPointInTriangle(v0,v1,v2,p) || ProjectedPointInTriangle(v0,v2,v3,p));
}

bool PlaneObject::ProjectedPointInTriangle(const Vector3f & v0,const Vector3f & v1,const Vector3f& v2, const Vector3f& p) const{
    float s0 = (v1 - v0).cross(p - v0).dot(m_normal);
    float s1 = (v2 - v1).cross(p - v1).dot(m_normal);
    float s2 = (v0 - v2).cross(p - v2).dot(m_normal);
    bool same_a = ((s0 >= 0) && (s1 >= 0) && (s2 >= 0));
    bool same_b = ((s0 <= 0) && (s1 <= 0) && (s2 <= 0));
    return (same_a || same_b);
}
