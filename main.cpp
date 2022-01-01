#include <iostream>
#include "core_types.h"
#include "force_simulation.h"
#include "movement_simulation.h"
#include <fstream>

using namespace std;


int main() {

    //Create new celestial bodies
    CelestialBody Sun("Sun", 1.98855e+18, {0,0,0}, {0,0,0});
    CelestialBody Earth("Earth", 5.97219e+12, {1.52098233e+8,0,0}, {0,29.290,0});

    //array of bodies
    CelestialBody bodies[] {Sun, Earth};

    int n_bodies = sizeof(bodies)/ sizeof(CelestialBody);

    //array of vector gravitational forces acting on bodies
    Vector3 grav_forces[n_bodies];

    // print info about bodies in sim
    cout<<Sun;
    cout<<Earth;

    //Create gravitational constant
    const float G = 6.6743e-8; // [G] = [km^3*GT^(-1)*s^(-2)]

    //Create variables for time control
    int dt = 24*60*60; //dt = 1 day
    int period = 365*24*60*60; // period = 1 year
    int time = 0;

    //Open files to save data
    ofstream ofileSun;
    ofileSun.open("Sun.txt");

    ofstream ofileEarth;
    ofileEarth.open("Earth.txt");

    //loop variables for the calculations
    int i,j,k;

    //Start simulation
    do
    {
        //save positions of bodies to file
        ofileSun << Sun.position;
        ofileEarth << Earth.position;

        //Calculate gravitational force between bodies
        for (i = 0; i < n_bodies-1; ++i) {
            for (j = i+1; j < n_bodies; ++j) {
                Vector3 Force = gravitational_force(G, bodies[i], bodies[j]);
                grav_forces[i] -= Force;
                grav_forces[j] += Force;
            }
        }

        //Move bodies
        for (k = 0; k < n_bodies; ++k) {
            sim_step(grav_forces[k], bodies[k], dt);
        }

        //Increment time
        time+=dt;
    }
    while(time <= period); //Stop simulation

    //Close files
    ofileSun.close();
    ofileEarth.close();

    return 0;
}
