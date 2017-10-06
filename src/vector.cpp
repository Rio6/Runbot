/*
 * Author: Rio
 * Date: 2017/10/05
 */

#include "vector.hpp"

using runbot::Vector;

Vector Vector::operator+(const Vector &rhs) {
    return Vector{x + rhs.x, y + rhs.y};
}

Vector Vector::operator-(const Vector &rhs) {
    return Vector{x - rhs.x, y - rhs.y};
}

Vector Vector::operator*(const Vector &rhs) {
    return Vector{x * rhs.x, y * rhs.y};
}

Vector Vector::operator/(const Vector &rhs) {
    return Vector{x / rhs.x, y / rhs.y};
}

Vector Vector::operator+(int rhs) {
    return Vector{x + rhs, y + rhs};
}

Vector Vector::operator-(int rhs) {
    return Vector{x - rhs, y - rhs};
}

Vector Vector::operator*(int rhs) {
    return Vector{x * rhs, y * rhs};
}

Vector Vector::operator/(int rhs) {
    return Vector{x / rhs, y / rhs};
}
