#ifndef SOLARSYSTEMSIM_FORCE_SIMULATION_H
#define SOLARSYSTEMSIM_FORCE_SIMULATION_H

#include "core_types.h"
#include <cmath>

//macro could be used for better performance
// [G] = [km^3*GT^(-1)*s^(-2)]
#define GRAVITATIONAL_CONSTANT 6.6743e-8

/// Calculates gravitational force between two bodies
/// Arguments:
/// CelestialBody& body1: body which gravitational force we are calculating
/// CelestialBody& body2: body which gravitational force we are calculating
Vector3 gravitational_force(CelestialBody& body1, CelestialBody& body2){
    //Gravitational_const must be float type
    float mass1 = body1.mass; //mass must be float type
    float mass2 = body2.mass;
    Vector3 pos1 = body1.position;
    Vector3 pos2 = body2.position;

    float distance2 = Vector3::distance2(pos1, pos2);
    float distance = sqrt(distance2);

    float force = -GRAVITATIONAL_CONSTANT*mass1*mass2/distance2;

    return (pos2-pos1) * (force/distance);
}


#endif //SOLARSYSTEMSIM_FORCE_SIMULATION_H
