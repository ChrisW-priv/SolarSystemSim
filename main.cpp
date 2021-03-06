#include <iostream>
#include "core_types.h"
#include "force_simulation.h"
#include "movement_simulation.h"
#include <ctime>
#include <fstream>

using std::cout, std::endl, std::string, std::ifstream, std::ofstream;

//change to 1 if you want a fast calculation using only sun as a body with gravitational significance
//change to 0 if you want to calculate the force between all bodies in the system
#define QUICK 1
//precision type for calculations in a Vector type
#define precision_type double
//number of seconds in a day
#define DAY 86'400
//number of seconds in a year (defined as a long long type)
#define YEAR (DAY*365LL)


int main() {
    //name of data input file
    string data = "input_data.txt";

    //Open a file with data
    ifstream read_file;
    read_file.open(data);

    if (!read_file) {
        cout << "couldn't open file!\n";
        exit(1);
    }
    int n_bodies; //number of bodies

    read_file >> n_bodies; 

    //array of bodies considered in simulation
    CelestialBody<precision_type> bodies[n_bodies];

    //read body data from an input file
    for(int i = 0; i < n_bodies; i++)
    {
        string name; //stores the name of celestial body
        double mass; //stores mass of celestial body
        precision_type coordinates[3]; //store coordinates of celestial body
        precision_type velocities[3]; //store velocities of celestial body

        read_file >> name;
        read_file >> mass;
        for(double & coordinate : coordinates)
            read_file >> coordinate;
        for(double & velocity : velocities)
            read_file >> velocity;

        Vector3<precision_type> Pos(coordinates); //position vector
        Vector3<precision_type> Vel(velocities); //velocity vector

        bodies[i] = CelestialBody<precision_type>(name, mass, Pos, Vel);
    }

    //Close the file with data
    read_file.close();

    // print info about bodies in sim
    for (CelestialBody<precision_type> body: bodies) {
        cout<<body;
    }

    //Create variables for time control
    constexpr uint8_t dt = 30; //dt = 0.5 minute
    constexpr uint64_t period = YEAR; // period = 1 year
    uint64_t time = 0;

    //array of files to save body positions to
    ofstream save_files[n_bodies];

    int body_index; //variable used in all loops over n_bodies in an array
    //open each file with name: name_of_body.txt
    for (body_index = 0; body_index < n_bodies; ++body_index) {
        save_files[body_index].open(string(bodies[body_index].name) + ".txt");
    }

    //loop variables for the calculations
    int i, j;
    // Array of Vector3 forces acting on body in simulation
    Vector3<precision_type> grav_forces[n_bodies];
    // Vector array of zeros used to reset the grav_force array after each loop
    Vector3<precision_type> VectorZero{0,0,0};

    clock_t req_time; //the value used to calculate the time the program requires to simulate the whole process
    req_time = clock(); //start the clock

    //Start simulation
    do {
        //save positions of bodies to file
        //saves every day
        if((time % DAY) == 0)
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
            grav_forces[body_index] = VectorZero;
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
