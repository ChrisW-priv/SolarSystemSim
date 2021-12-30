#include <iostream>
#include "core_types.h"
#include "force_simulation.h"
#include "movement_simulation.h"
#include <fstream>

using namespace std;

//A function showing infos about celestial bodies
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

    CelestialBodyInfo(Sun);
    CelestialBodyInfo(Earth);

    //Create gravitational constant
    const float G = 6.6743e-8; // [G] = [km^3*GT^(-1)*s^(-2)]

    //Create variables for time control
    float dt = 24*60*60;
    float period = 365*24*60*60;
    float time = 0;

    //Open files to save data
    ofstream ofileSun;
    ofileSun.open("Sun.txt");

    ofstream ofileEarth;
    ofileEarth.open("Earth.txt");

    //Start simulation
    do
    {
        //Calculating gravitational force
        Vector3 ForceEarth = gravitational_force(G, Sun, Earth);
        Vector3 ForceSun;
        ForceSun = ForceEarth * (-1);

        //save positions of bodies
        //ofileSun << time << "\t" ;
        ofileSun << Sun.position.x() << "\t" << Sun.position.y() << "\t" << Sun.position.z() << endl;

        //ofileEarth << time << "\t\t" ;
        ofileEarth << Earth.position.x() << "\t" << Earth.position.y() << "\t" << Earth.position.z() << endl;

        //Move bodies
        sim_step(ForceSun, Sun, dt);
        sim_step(ForceEarth, Earth, dt);

        //Increment time
        time+=dt;
    }
    while(time <= period);

    //Stop simulation

    //Close files
    ofileSun.close();
    ofileEarth.close();

    return 0;
}
