#ifndef SOLARSYSTEMSIM_MOVEMENT_SIMULATION_H_
#define SOLARSYSTEMSIM_MOVEMENT_SIMULATION_H_

#include "core_types.h"
#include "force_simulation.h"
#include <cmath>

Vector3 acceleration(Vector3& gravitational_force, CelestialBody& body){
	float a_x = gravitational_force.x() / body.mass;
	float a_y = gravitational_force.y() / body.mass;
	float a_z = gravitational_force.z() / body.mass;

	return {a_x, a_y, a_z};
	//returns acceleration of a celestial body
}

Vector3 new_velocity(Vector3& acceleration, CelestialBody& body, int dt)
{
	float v_x = body.velocity.x() + acceleration.x() * dt;
	float v_y = body.velocity.y() + acceleration.y() * dt;
	float v_z = body.velocity.z() + acceleration.z() * dt;

	return {v_x, v_y, v_z};
}

Vector3 new_posiotion(Vector3& velocity, CelestialBody& body, int dt)
{
	float x = body.position.x() + velocity.x() * dt;
	float y = body.position.y() + velocity.y() * dt;
	float z = body.position.z() + velocity.z() * dt;

	return {x,y,z};
}

void sim_step(Vector3& gravitational_force, CelestialBody& body, int dt)
{
	Vector3 a; //acceleration of a body
    Vector3 v; //velocity of a body
    Vector3 pos; //position of a body

    a = acceleration(gravitational_force, body);
    v = new_velocity(a, body, dt);
    pos = new_posiotion(v, body, dt);

    body.velocity = v;
    body.position = pos;
}

#endif //SOLARSYSTEMSIM_MOVEMENT_SIMULATION_H_