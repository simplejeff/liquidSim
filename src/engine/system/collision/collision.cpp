#include "engine/system/collision/collision.h"
#include <algorithm>

Collision::Collision():m_is_collision(false){

}

Collision::Collision(const Vector3f& normal,float collision_distance,bool is_collision):m_normal(normal),m_collision_distance(collision_distance),m_is_collision(is_collision)
{
    //ctor
}

Collision::~Collision()
{
    //dtor
}
