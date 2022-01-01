#include <iostream>
#include "core_types.h"
#include "force_simulation.h"
#include "movement_simulation.h"
#include <fstream>

using namespace std;


int main() {

    //Create new celestial bodies
    CelestialBody Sun("Sun", 1.98855e+18, {0, 0, 0}, {0, 0, 0});
    CelestialBody Earth("Earth", 5.97219e+12, {1.52098233e+8, 0, 0}, {0, 29.290, 0});

    //array of bodies
    CelestialBody bodies[]{Sun, Earth};

    int n_bodies = sizeof(bodies) / sizeof(CelestialBody);

    // print info about bodies in sim
    for (CelestialBody body: bodies) {
        cout<<body;
    }

    //Create gravitational constant
    const float G = 6.6743e-8; // [G] = [km^3*GT^(-1)*s^(-2)]

    //Create variables for time control
    int dt = 24 * 60 * 60; //dt = 1 day
    int period = 365 * 24 * 60 * 60; // period = 1 year
    int time = 0;

    //array of files to save body positions to
    ofstream save_files[n_bodies];

    int body_index; //variable used in all loops over n_bodies in an array
    //open each file with name: name_of_body.txt
    for (body_index = 0; body_index < n_bodies; ++body_index) {
        save_files[body_index].open(string(bodies[body_index].name) + ".txt");
    }

    //loop variables for the calculations
    int i, j;
    Vector3 grav_forces[n_bodies]; // Array of Vector3 forces acting on body in simulation
    Vector3 VectorZeros[n_bodies]; // Vector array of zeros used to reset the grav_force array after each loop

    //Start simulation
    do {
        //save positions of bodies to file
        for (body_index = 0; body_index < n_bodies; ++body_index) {
            save_files[body_index] << bodies[body_index].position;
        }

        //Calculate gravitational force between bodies
        for (i = 0; i < n_bodies - 1; ++i){
            for (j = i + 1; j < n_bodies; ++j){
                Vector3 Force = gravitational_force(G, bodies[i], bodies[j]);
                grav_forces[i] -= Force;
                grav_forces[j] += Force;
            }
        }

        //Move bodies
        for (body_index = 0; body_index < n_bodies; ++body_index){
            sim_step(grav_forces[body_index], bodies[body_index], dt);
        }

        //reset gravitational force array to zeros
        for (body_index = 0; body_index < n_bodies; body_index++){
            grav_forces[body_index] = VectorZeros[body_index];
        }

        //Increment time
        time += dt;
    } while (time <= period); //Stop simulation

    //Close files
    for (body_index = 0; body_index < n_bodies; ++body_index) {
        save_files[body_index].close();
    }
}
