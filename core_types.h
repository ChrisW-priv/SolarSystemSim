#ifndef SOLARSYSTEMSIM_CORE_TYPES_H
#define SOLARSYSTEMSIM_CORE_TYPES_H

#include <iostream>


struct Vector3{
    //array of floats holding the data
    float value[3]{};

    Vector3();
    explicit Vector3(const float arr[]);
    Vector3(float x, float y, float z);

    Vector3 operator + (const Vector3& other);
    Vector3 operator - (const Vector3& other);
    Vector3 operator * (float a);
    Vector3 &operator = (const Vector3& other);

    Vector3 power2();
    static float element_sum(Vector3& vector);
    static float distance2(Vector3& v1, Vector3& v2);

    float x();
    float y();
    float z();

    static float diff_x(Vector3& v1, Vector3& v2);
    static float diff_y(Vector3& v1, Vector3& v2);
    static float diff_z(Vector3& v1, Vector3& v2);

    //standard output for a vector type: prfloat type and x,y,z values
    friend std::ostream& operator << (std::ostream& stream, const Vector3& vector){
        stream << "Vector3:" << " x: " << vector.value[0] << " y: " << vector.value[1] << " z: " << vector.value[2] << "\n";
        return stream;
    }
};


struct CelestialBody{
    char name[32];
    float mass; //mass must be float type
    Vector3 position;
    Vector3 velocity;

    CelestialBody(const std::string& name, float mass, Vector3 position, Vector3 velocity) : name(), mass(){
        name.copy(this->name, 32);
        this->mass = mass;
        this->position = position;
        this->velocity = velocity;
    }
};

#endif //SOLARSYSTEMSIM_CORE_TYPES_H
