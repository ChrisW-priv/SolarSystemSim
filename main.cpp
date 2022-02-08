#include <iostream>
#include "core_types.h"
#include "force_simulation.h"
#include "movement_simulation.h"
#include <ctime>
#include <fstream>

using namespace std;

//change to 1 if you want a fast calculation using only sun as a body with gravitational significance
//change to 0 if you want to calculate the force between all bodies in the system
#define QUICK 0
#define precision_type double


int main() {

    //Create new celestial bodies
    CelestialBody<precision_type> Sun("Sun", 1.9885e+18, {0, 0, 0}, {0, 0, 0});
    CelestialBody<precision_type> Mercury("Mercury", 3.302e+11, {4.531326897276655E+07, 1.974713223060311E+07, -2.542760719451804E+06}, {-2.893829994122281E+01, 4.681410329201923E+01, 6.479990726169209E+00});
    CelestialBody<precision_type> Venus("Venus", 4.8685e+12, {-2.805660750540954E+07, 1.037845779199983E+08, 3.043432754529312E+06}, {-3.392562841966978E+01, -9.334471369461159E+00, 1.829532551283318E+00});
    CelestialBody<precision_type> Earth("Earth", 5.97219e+12, {-4.140619158118801E+07, 1.411596415319905E+08, -6.282350952059031E+03}, {-2.907331218841453E+01, -8.508702615200745E+00, 3.489542068435547E-04});
    CelestialBody<precision_type> Mars("Mars", 6.4171e+11, {-1.186388601698978E+08, -1.955390170872595E+08, -1.187851245239288E+06}, {2.162433230973008E+01, -1.049056189150711E+01, -7.503002777178573E-01});
    CelestialBody<precision_type> Jupiter("Jupiter", 1.89818722e+15, {6.991658487523705E+08, -2.618055853972343E+08, -1.455520416577217E+07}, {4.430554871607745E+00, 1.286461152124837E+01, -1.525212397130042E-01});
    CelestialBody<precision_type> Saturn("Saturn", 5.6834e+14, {1.044498730885592E+09, -1.053634891773224E+09,-2.324897738836139E+07}, {6.326428746330373E+00, 6.793067920763237E+00, -3.699678920016645E-01});
    CelestialBody<precision_type> Uranus("Uranus", 8.6813e+13, {2.151415864225246E+09, 2.018805429024650E+09, -2.038162913815439E+07}, {-4.706564257756637E+00, 4.661521797450809E+00, 7.809125466736888E-02});
    CelestialBody<precision_type> Neptune("Neptune", 1.02409e+14, {4.433442236504333E+09, -6.091337599094089E+08, -8.963575155197549E+07}, {7.090104763934740E-01, 5.432245682893912E+00, -1.273439127752560E-01});
    CelestialBody<precision_type> Pluto("Pluto", 1.307e+10, {2.265531048060069E+09, -4.624183920294006E+09, -1.602159767424855E+08}, {5.034427840434326E+00, 1.236597030973408E+00, -1.597597645662122E+00});

    //array of bodies
    CelestialBody<precision_type> bodies[]{Sun, Mercury, Venus, Earth, Mars, Jupiter, Saturn, Uranus, Neptune, Pluto};

    int n_bodies = sizeof(bodies) / sizeof(CelestialBody<precision_type>);

    // print info about bodies in sim
    for (CelestialBody<precision_type> body: bodies) {
        cout<<body;
    }

    //Create variables for time control
    int dt = 60; //dt = 1 minute
    long long int period = 365 * 24 * 3600; // period = 1 year
    long long int time = 0;

    //array of files to save body positions to
    ofstream save_files[n_bodies];

    int body_index; //variable used in all loops over n_bodies in an array
    //open each file with name: name_of_body.txt
    for (body_index = 0; body_index < n_bodies; ++body_index) {
        save_files[body_index].open(string(bodies[body_index].name) + ".txt");
    }

    //loop variables for the calculations
    int i, j;
    Vector3<precision_type> grav_forces[n_bodies]; // Array of Vector3 forces acting on body in simulation
    Vector3<precision_type> VectorZeros[n_bodies]; // Vector array of zeros used to reset the grav_force array after each loop

    clock_t req_time; //the value used to calculate the time the program requires to simulate the whole process
    req_time = clock(); //start the clock

    //Start simulation
    do {
        //save positions of bodies to file
        if((time%3600) == 0)
        {
            for (body_index = 0; body_index < n_bodies; ++body_index) {
                save_files[body_index] << bodies[body_index].position;
            }
        }

        //Calculate gravitational force between bodies
        #if QUICK
            //schema for simulation just counting the sun as a body that is relevant for the system
            for (i=1; i<n_bodies; i++){
                Vector3<precision_type> Force = gravitational_force(bodies[0], bodies[i]);
                grav_forces[0] -= Force;
                grav_forces[i] += Force;
            }
        #else
            for (i = 0; i < n_bodies - 1; ++i) {
                for (j = i + 1; j < n_bodies; ++j) {
                    Vector3<precision_type> Force = gravitational_force<precision_type>(bodies[i], bodies[j]);
                    grav_forces[i] -= Force;
                    grav_forces[j] += Force;
                }
            }
        #endif

        //Move bodies
        for (body_index = 0; body_index < n_bodies; ++body_index){
            sim_step<precision_type>(grav_forces[body_index], bodies[body_index], dt);
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

    req_time = clock() - req_time; //stop the clock
    cout << "The simulation took " << (float)req_time/CLOCKS_PER_SEC << " s" << endl; //time output
}
