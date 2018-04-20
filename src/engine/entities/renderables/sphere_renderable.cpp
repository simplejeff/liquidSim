#include "sphere_renderable.h"
#include <GL/freeglut.h>

SphereRenderable::SphereRenderable(Sphere * geom_entity):RenderableEntity(geom_entity){}

SphereRenderable::~SphereRenderable()
{
    //dtor
}

void SphereRenderable::Render(Graphics *g) const{
    Vector3f translate = m_geom_entity->GetTransformEntity()->GetTranslate();
    g->translate(glm::vec3(translate(0),translate(1),translate(2)));
    Sphere * sphere_entity = (Sphere *)m_geom_entity;
    g->setColor(glm::vec4(m_color(0),m_color(1),m_color(2), 255.f));
    g->scale(sphere_entity->GetRadius());
    g->drawShape("sphere");
    g->clearTransform();
}
