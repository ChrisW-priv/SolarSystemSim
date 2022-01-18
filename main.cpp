#include <iostream>
#include "core_types.h"
#include "force_simulation.h"
#include "movement_simulation.h"
#include <fstream>

using namespace std;

//change to 1 if you want a fast calculation using only sun as a body with gravitational significance
//change to 0 if you want to calculate the force between all bodies in the system
#define QUICK 0

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
        #if QUICK
            //schema for simulation just counting the sun as a body that is relevant for the system
            for (i=1; i<n_bodies; i++){
                Vector3 Force = gravitational_force(bodies[0], bodies[i]);
                grav_forces[0] -= Force;
                grav_forces[i] += Force;
            }
        #else
            for (i = 0; i < n_bodies - 1; ++i) {
                for (j = i + 1; j < n_bodies; ++j) {
                    Vector3 Force = gravitational_force(bodies[i], bodies[j]);
                    grav_forces[i] -= Force;
                    grav_forces[j] += Force;
                }
            }
        #endif

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
