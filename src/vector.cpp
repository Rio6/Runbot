/*
 * Author: Rio
 * Date: 2017/10/05
 */

#include "vector.hpp"

using runbot::Vector;

Vector Vector::operator+(const Vector &lhs) {
    return Vector{x + lhs.x, y + lhs.y};
}

Vector Vector::operator-(const Vector &lhs) {
    return Vector{x - lhs.x, y - lhs.y};
}

Vector Vector::operator*(const Vector &lhs) {
    return Vector{x * lhs.x, y * lhs.y};
}

Vector Vector::operator/(const Vector &lhs) {
    return Vector{x / lhs.x, y / lhs.y};
}

Vector Vector::operator+(int lhs) {
    return Vector{x + lhs, y + lhs};
}

Vector Vector::operator-(int lhs) {
    return Vector{x - lhs, y - lhs};
}

Vector Vector::operator*(int lhs) {
    return Vector{x * lhs, y * lhs};
}

Vector Vector::operator/(int lhs) {
    return Vector{x / lhs, y / lhs};
}
