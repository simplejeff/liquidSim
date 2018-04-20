#include "engine/entities/misc/transform_entity.h"
#include <GL/freeglut.h>

TransformEntity::TransformEntity()
{
    //ctor
    m_translate = Vector3f(0,0,0);
}



TransformEntity::~TransformEntity()
{
    //dtor
}
