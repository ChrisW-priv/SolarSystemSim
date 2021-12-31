#include <iostream>
#include "core_types.h"
#include "force_simulation.h"
#include "movement_simulation.h"
#include <fstream>

using namespace std;

/// Function showing infos about celestial bodies
void CelestialBodyInfo(CelestialBody &body)
{
    cout << "Name: " << body.name << endl;
    cout << "Mass: " << body.mass << " GT" << endl;
    cout << "Position [km]: " << body.position;
    cout << "Velocity [km/s]: " << body.velocity << endl;
}

int main() {

    //Create new celestial bodies
    CelestialBody Sun("Sun", 1.98855e+18, {0,0,0}, {0,0,0});
    CelestialBody Earth("Earth", 5.97219e+12, {1.52098233e+8,0,0}, {0,29.290,0});

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

    //Start simulation
    do
    {
        //save positions of bodies to file
        ofileSun << Sun.position;
        ofileEarth << Earth.position;

        //Calculate gravitational force between bodies
        Vector3 ForceEarth = gravitational_force(G, Sun, Earth);
        Vector3 ForceSun;
        ForceSun = ForceEarth * (-1);

        //Move bodies
        sim_step(ForceSun, Sun, dt);
        sim_step(ForceEarth, Earth, dt);

        //Increment time
        time+=dt;
    }
    while(time <= period); //Stop simulation

    //Close files
    ofileSun.close();
    ofileEarth.close();

    return 0;
}
