#ifndef SOLARSYSTEMSIM_FORCE_SIMULATION_H
#define SOLARSYSTEMSIM_FORCE_SIMULATION_H

#include "core_types.h"
#include <cmath>


Vector3 gravitational_force(float Gravitational_const, CelestialBody& body1, CelestialBody& body2){
    //Gravitational_const must be float type
    float mass1 = body1.mass; //mass must be float type
    float mass2 = body2.mass;
    Vector3 pos1 = body1.position;
    Vector3 pos2 = body2.position;

    float distance2 = Vector3::distance2(pos1, pos2);
    float distance = sqrt(distance2);

    float force = -Gravitational_const*(mass1*mass2/distance2);

    float dx = Vector3::diff_x(pos1, pos2);
    float dy = Vector3::diff_y(pos1, pos2);
    float dz = Vector3::diff_z(pos1, pos2);

    float Fx = force * dx / distance;
    float Fy = force * dy / distance;
    float Fz = force * dz / distance;

    return {Fx, Fy, Fz};
}


#endif //SOLARSYSTEMSIM_FORCE_SIMULATION_H
