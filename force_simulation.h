#ifndef SOLARSYSTEMSIM_FORCE_SIMULATION_H
#define SOLARSYSTEMSIM_FORCE_SIMULATION_H

#include "core_types.h"
#include <cmath>


Vector3 gravitational_force(int Gravitational_const, CelestialBody& body1, CelestialBody& body2){
    int mass1 = body1.mass;
    int mass2 = body2.mass;
    Vector3 pos1 = body1.position;
    Vector3 pos2 = body2.position;

    float distance2 = Vector3::distance2(pos1, pos2);
    float distance = sqrt(distance2);

    float force = -Gravitational_const*(mass1*mass2/distance2);

    return (pos2-pos1) * (force/distance);
}


#endif //SOLARSYSTEMSIM_FORCE_SIMULATION_H
