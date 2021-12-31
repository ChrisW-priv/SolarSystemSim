#ifndef SOLARSYSTEMSIM_MOVEMENT_SIMULATION_H_
#define SOLARSYSTEMSIM_MOVEMENT_SIMULATION_H_

#include "core_types.h"
#include "force_simulation.h"
#include <cmath>


/// Calculates acceleration of the body
/// Arguments:
/// Vector3& gravitational_force: force acting on a body
/// CelestialBody& body: body which acceleration we are calculating
/// float dt: time step of the simulation
Vector3 acceleration(Vector3& gravitational_force, CelestialBody& body){
    return gravitational_force* (1/body.mass);
	//returns acceleration of a celestial body
}

/// Calculates new velocity
/// Arguments:
/// Vector3& acceleration: acceleration acting on a body
/// CelestialBody& body: body which new velocity we are calculating
/// float dt: time step of the simulation
Vector3 new_velocity(Vector3& acceleration, CelestialBody& body, float dt)
{
    return body.velocity + acceleration * dt;
}

/// Calculates new position
/// Arguments:
/// Vector3& acceleration: acceleration acting on a body
/// CelestialBody& body: body which new position we are calculating
/// float dt: time step of the simulation
Vector3 new_position(Vector3& acceleration, CelestialBody& body, float dt)
{
    return body.position + body.velocity * dt + acceleration * 0.5 * pow(dt, 2);
}

/// Changes CelestialBody properties over each sim step
/// Arguments:
/// Vector3 gravitational_force: force acting on a body
/// CelestialBody body: object that we change properties of
/// float dt: time step of the simulation
void sim_step(Vector3& gravitational_force, CelestialBody& body, float dt)
{
	Vector3 a = acceleration(gravitational_force, body); //acceleration of a body

    body.velocity = new_velocity(a, body, dt); //velocity of a body;
    body.position = new_position(a, body, dt); //position of a body
}

#endif //SOLARSYSTEMSIM_MOVEMENT_SIMULATION_H_