#ifndef SOLARSYSTEMSIM_CORE_TYPES_H
#define SOLARSYSTEMSIM_CORE_TYPES_H

#include <iostream>
#include <cmath>


template<typename T>
struct Vector3{
    //array 3 values of type specified
    T value[3]{};

    /// if no source provided - innit Vector3 to a zero vector
    Vector3() = default;

    /// constructing from an array of elements
    explicit Vector3(const T arr[]) : value() {
        for (int i = 0; i < 3; ++i) {
            value[i] = arr[i];
        }
    }

    /// constructor from 3 values provided
    Vector3(T x, T y, T z) : value(){
        value[0] = x;
        value[1] = y;
        value[2] = z;
    }

    Vector3<T> operator + (const Vector3<T> &other) {
        Vector3<T> new_vector;
        for (int i = 0; i < 3; ++i) {
            new_vector.value[i] = this->value[i] + other.value[i];
        }
        return new_vector;
    }

    void operator += (const Vector3& other) {
        for (int i = 0; i < 3; ++i) {
            this->value[i] = this->value[i] + other.value[i];
        }
    }

    Vector3<T> operator - (const Vector3& other){
        Vector3 new_vector;
        for (int i = 0; i < 3; ++i) {
            new_vector.value[i] = this->value[i] - other.value[i];
        }
        return new_vector;
    }

    void operator -= (const Vector3& other){
        for (int i = 0; i < 3; ++i) {
            this->value[i] = this->value[i] - other.value[i];
        }
    }

    Vector3<T> operator * (T a){
        Vector3<T> new_vector;
        for (int i = 0; i < 3; ++i) {
            new_vector.value[i] = this->value[i] * a;
        }
        return new_vector;
    }

    Vector3<T> &operator = (const Vector3& other){
        if(&other==this){ return *this; }
        else{
            value[0] = other.value[0];
            value[1] = other.value[1];
            value[2] = other.value[2];
            return *this;
        }
    };

    /// square Vector3 elements in place
    static void square_elements(Vector3<T>& vector){
        for (int i = 0; i < 3; ++i) {
            vector.value[i] = pow(vector.value[i], 2);
        }
    }

    /// returns new vector with each value squared
    Vector3<T> power2() {
        Vector3<T> new_vector = *this;
        return Vector3<T>::square_elements(new_vector);
    };

    /// sums all elements of the vector
    static T element_sum(Vector3<T>& vector) {
        T sum=0;
        for (T i : vector.value) {
            sum += i;
        }
        return sum;
    }

    /// returns a square of distance between two points represented by Vector3
    static T distance2(Vector3<T>& vector1, Vector3<T>& vector2) {
        Vector3<T> temp = vector1 - vector2;
        Vector3<T>::square_elements(temp);
        return Vector3<T>::element_sum( temp );
    }

    /// standard output for a vector type info: print x,y,z values separated by "\t" sign
    friend std::ostream& operator << (std::ostream& stream, const Vector3& vector){
        stream << vector.value[0] << "\t" << vector.value[1] << "\t" << vector.value[2] << "\n";
        return stream;
    }
};


template<typename T>
struct CelestialBody{
    char name[16];
    float mass;
    Vector3<T> position;
    Vector3<T> velocity;

    explicit CelestialBody(const std::string& name = "no_name", double mass = 0, Vector3<T> position = Vector3<T>(0,0,0), Vector3<T> velocity = Vector3<T>(0,0,0)) : name(), mass(){
        name.copy(this->name, 32);
        this->mass = mass;
        this->position = position;
        this->velocity = velocity;
    }

    /// standard output for a vector type info: print x,y,z values separated by "\t" sign
    friend std::ostream& operator << (std::ostream& stream, const CelestialBody& body){
        stream << "Name: " << body.name << "\n";
        stream << "Mass: " << body.mass << " GT" << "\n";
        stream << "Position [km]: " << body.position; //new line included in Vector3 std output
        stream << "Velocity [km/s]: " << body.velocity << "\n";
        return stream;
    }
};

#endif //SOLARSYSTEMSIM_CORE_TYPES_H
