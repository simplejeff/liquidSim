#include "particle_system_generator.h"
#include "engine/entities/geometry/sphere.h"
#include "engine/entities/renderables/sphere_renderable.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>

ParticleSystemGenerator::ParticleSystemGenerator()
{
    //ctor
    srand(time(NULL));   // should only be called once
}

ParticleSystemWorldEntity * ParticleSystemGenerator::GenerateCubeOfSpheres(const Vector3f& origin,const Vector3f& side_0_end,const Vector3f& side_1_end,size_t num_per_side,const Vector3f& color,float coeff_res,float coeff_fric,bool random_velocities){
    Vector3f d0 = side_0_end - origin;
    Vector3f d1 = side_1_end - origin;
    float l = d0.norm();
    Vector3f d2;
    d2 = d0.cross(d1).normalized()*l;
    float dx = l/((float)(num_per_side));
    size_t num_particles = num_per_side*num_per_side*num_per_side;
    Vector3f origin_offset = origin + .5*dx*d0 + .5*dx*d1 + .5*dx*d2;
    VectorXf m(num_particles);
    m = MatrixXf::Constant(num_particles,1,1.0);
    VectorXf q(num_particles*2*3);
    q = MatrixXf::Zero(num_particles*2*3,1);
    for(size_t k = 0;k<num_per_side;k++){
        for(size_t j = 0;j<num_per_side;j++){
            for(size_t i = 0;i<num_per_side;i++){
                size_t index = 3*CubeIndex(i,j,k,num_per_side);
                Vector3f pos;
                pos = origin_offset + i*dx*d0 + j*dx*d1 + k*dx*d2;
                q(index) = pos(0);
                q(index + 1) = pos(1);
                q(index + 2) = pos(2);
                if(random_velocities){
                    float v_x = 2*((rand() % 1000)/1000.0) - 1.0;
                    float v_y = 2*((rand() % 1000)/1000.0) - 1.0;
                    float v_z = 2*((rand() % 1000)/1000.0) - 1.0;
                    int v_index = 3*(num_particles) + index;
                    q(v_index) = v_x;
                    q(v_index + 1) = v_y;
                    q(v_index + 2) = v_z;
                }
            }
        }
    }
    TransformEntity * default_transform = new TransformEntity();
    Sphere * sphere = new Sphere(default_transform,Vector3f(0,0,0),dx*.5);
    SphereRenderable * sphere_renderable = new SphereRenderable(sphere);
    sphere_renderable->SetColor(color);
    ParticleSystemRenderable * renderable_entity = new ParticleSystemRenderable(sphere_renderable);

    ParticleSystemEntity  * physics_entity = new ParticleSystemEntity(NULL,m,q);
    physics_entity->SetCoefficientRestitution(coeff_res);
    physics_entity->SetCoefficientFriction(coeff_fric);

    return new ParticleSystemWorldEntity(physics_entity,renderable_entity);

}


ParticleSystemGenerator::~ParticleSystemGenerator()
{
    //dtor
}

size_t ParticleSystemGenerator::CubeIndex(size_t i,size_t j,size_t k,size_t n) const{
    return n*n*k + n*j + i;
}

