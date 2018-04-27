#ifndef PARTICLE_GENERATOR_H
#define PARTICLE_GENERATOR_H

#include <Eigen/Dense>
using namespace Eigen;

void InitRandom();

float Random();

VectorXf GenParticleInCube(size_t,float);

VectorXf GenRandomVelocities(size_t);


#endif // PARTICLE_GENERATOR_H
