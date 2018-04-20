#include "cube_renderable.h"
#include "engine/entities/geometry/cube_entity.h"
#include <GL/freeglut.h>

CubeRenderable::CubeRenderable(GeomEntity * geom_entity):RenderableEntity(geom_entity)
{
    //ctor
}

CubeRenderable::~CubeRenderable()
{
    //dtor
}


void CubeRenderable::Render(Graphics *g) const{
    Vector3f translate = m_geom_entity->GetTransformEntity()->GetTranslate();
    g->translate(glm::vec3(translate(0), translate(1), translate(2)));
    float width = ((CubeEntity*)m_geom_entity)->GetWidth();
    std::cout << " width : " << width << std::endl;
    g->setColor(glm::vec4(m_color(0),m_color(1),m_color(2), 255.f));
    g->scale(width);
    g->drawShape("cube");
    g->clearTransform();
}
