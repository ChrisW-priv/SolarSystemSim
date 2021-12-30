#ifndef SOLARSYSTEMSIM_MOVEMENT_SIMULATION_H_
#define SOLARSYSTEMSIM_MOVEMENT_SIMULATION_H_

#include "core_types.h"
#include "force_simulation.h"
#include <cmath>

Vector3 acceleration(Vector3& gravitational_force, CelestialBody& body){
    return gravitational_force* (1/body.mass);
	//returns acceleration of a celestial body
}

Vector3 new_velocity(Vector3& acceleration, CelestialBody& body, float dt)
{
    return (body.velocity + acceleration) * dt;
}

Vector3 new_posiotion(Vector3& acceleration, CelestialBody& body, float dt)
{
    return body.position + body.velocity * dt + acceleration * 0.5 * pow(dt, 2);
}

void sim_step(Vector3& gravitational_force, CelestialBody& body, float dt)
{
	Vector3 a; //acceleration of a body
    Vector3 v; //velocity of a body
    Vector3 pos; //position of a body

    a = acceleration(gravitational_force, body);
    v = new_velocity(a, body, dt);
    pos = new_posiotion(a, body, dt);

    body.velocity = v;
    body.position = pos;
}

#endif //SOLARSYSTEMSIM_MOVEMENT_SIMULATION_H_