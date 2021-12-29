#include "core_types.h"
#include <cmath>


Vector3::Vector3() : value() {
    for (float & i : value) { i = 0; }
}

Vector3::Vector3(const float arr[]) : value() {
    for (int i = 0; i < 3; ++i) {
        value[i] = arr[i];
    }
}
Vector3::Vector3(float x, float y, float z) : value(){
    value[0] = x;
    value[1] = y;
    value[2] = z;
}

Vector3 Vector3::operator+(const Vector3 &other) {
    Vector3 new_vector;
    for (int i = 0; i < 3; ++i) {
        new_vector.value[i] = this->value[i] + other.value[i];
    }
    return new_vector;
}

Vector3 Vector3::operator-(const Vector3 &other) {
    Vector3 new_vector;
    for (int i = 0; i < 3; ++i) {
        new_vector.value[i] = this->value[i] - other.value[i];
    }
    return new_vector;
}

Vector3 Vector3::operator*(float a) {
    Vector3 new_vector;
    for (int i = 0; i < 3; ++i) {
        new_vector.value[i] = this->value[i] * a;
    }
    return new_vector;
}

float Vector3::x() {
    return this->value[0];
}

float Vector3::y() {
    return this->value[1];
}

float Vector3::z() {
    return this->value[2];
}

Vector3 Vector3::power2() {
    Vector3 new_vector;
    for (int i = 0; i < 3; ++i) {
        new_vector.value[i] = pow(this->value[i], 2);
    }
    return new_vector;
}

float Vector3::element_sum(Vector3& vector) {
    float sum=0;
    for (float i : vector.value) {
        sum += i;
    }
    return sum;
}

float Vector3::distance2(Vector3& vector1, Vector3& vector2) {
    Vector3 temp = (vector2 - vector1).power2();
    return Vector3::element_sum( temp );
}

float Vector3::diff_x(Vector3 &v1, Vector3 &v2) {
    return v1.x() - v2.x();
}

float Vector3::diff_y(Vector3 &v1, Vector3 &v2) {
    return v1.y() - v2.y();
}

float Vector3::diff_z(Vector3 &v1, Vector3 &v2) {
    return v1.z() - v2.z();
}





