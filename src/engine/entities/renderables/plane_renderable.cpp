#include "plane_renderable.h"
#include <GL/freeglut.h>

PlaneRenderable::PlaneRenderable(PlaneEntity * plane_entity):RenderableEntity(plane_entity)
{
    //ctor
    std::vector<float> shapedata = std::vector<float>();
    PlaneEntity * plane = (PlaneEntity *)m_geom_entity;
    Vector3f bot1 = plane->GetV2();
    Vector3f bot2 =  plane->GetV1();
    Vector3f bot3 =  plane->GetV3();
    Vector3f bot4 =  plane->GetV0();
    Vector3f botnorm =  plane->GetNormal();
    Vector2f texture = Vector2f(0.f, 0.f);
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

PlaneRenderable::~PlaneRenderable()
{
    //dtor
}

void PlaneRenderable::Render(Graphics *g) const{
    Vector3f translate = m_geom_entity->GetTransformEntity()->GetTranslate();
   std::cout << "translate : " << translate[0] << "," << translate[1] << "," << translate[2] << std::endl;
    g->translate(glm::vec3(translate[0], translate[1], translate[2]));
    m_shape->draw(g);
    g->clearTransform();
}

