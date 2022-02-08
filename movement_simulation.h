#ifndef SOLARSYSTEMSIM_MOVEMENT_SIMULATION_H_
#define SOLARSYSTEMSIM_MOVEMENT_SIMULATION_H_

#include "core_types.h"
#include "force_simulation.h"


/// Changes CelestialBody properties over each sim step
/// Arguments:
/// Vector3 gravitational_force: force acting on a body
/// CelestialBody body: object that we change properties of
/// float dt: time step of the simulation
template<typename T>
void sim_step(Vector3<T>& gravitational_force, CelestialBody<T>& body, float dt)
{
    Vector3<T> acceleration_times_dt = gravitational_force * (dt/body.mass); //acceleration of a body

    body.velocity += acceleration_times_dt; //velocity of a body
    body.position += body.velocity * dt + acceleration_times_dt * (dt / 2); //position of a body
}

#endif //SOLARSYSTEMSIM_MOVEMENT_SIMULATION_H_