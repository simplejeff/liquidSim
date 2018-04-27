#include "particle_generator.h"
#include <time.h>
#include <stdlib.h>

void InitRandom(){
    srand(time(NULL));
}

float Random(){
    return (rand() % 1000) / 1000.0;
}

VectorXf GenParticleInCube(size_t num_per_side,float side_length){
    size_t n2 = num_per_side*num_per_side;
    size_t n3 = n2*num_per_side;
    VectorXf particles(n3*3,1);
    float s2 = side_length/2.0;
    Vector3f v0 = Vector3f(-s2,-s2,s2);
    Vector3f v1 = Vector3f(s2,-s2,s2);
    Vector3f v2 = Vector3f(-s2,-s2,-s2);
    Vector3f v01 = v1 - v0;
    Vector3f v02 = v2 - v0;
    Vector3f v03 = v01.cross(v02).normalized()*side_length;
    float dx = side_length/num_per_side;
    for(size_t k = 0; k < num_per_side;k++){
        for(size_t j = 0; j < num_per_side;j++){
            for(size_t i = 0; i < num_per_side;i++){
                size_t index = n2*k + num_per_side*j + i;
                size_t new_index = 3*index;
                Vector3f p = v0 + dx*i*v01 + dx*j*v02 + dx*k*v03;
                particles(new_index) = p(0);
                particles(new_index + 1) = p(1);
                particles(new_index + 2) = p(2);
            }
        }
    }
    return particles;
}

VectorXf GenRandomVelocities(size_t n){
    VectorXf v(3*n,1);
    for(size_t i = 0;i<3*n;i+=3){
        float x = 2*Random() - 1.0;
        float y = 2*Random() - 1.0;
        float z = 2*Random() - 1.0;
        v(i) = x;
        v(i + 1) = y;
        v(i + 2) = z;
    }
    return v;
}
