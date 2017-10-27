/*
 * Author: Rio
 * Date: 2017/10/27
 */

#include "vector.hpp"

using runbot::Vector;

Vector Vector::operator+(const Vector &rhs) const {
    return Vector{x + rhs.x, y + rhs.y};
}

Vector Vector::operator-(const Vector &rhs) const {
    return Vector{x - rhs.x, y - rhs.y};
}

Vector Vector::operator*(const Vector &rhs) const {
    return Vector{x * rhs.x, y * rhs.y};
}

Vector Vector::operator/(const Vector &rhs) const {
    return Vector{x / rhs.x, y / rhs.y};
}

Vector Vector::operator+(int rhs) const {
    return Vector{x + rhs, y + rhs};
}

Vector Vector::operator-(int rhs) const {
    return Vector{x - rhs, y - rhs};
}

Vector Vector::operator*(int rhs) const {
    return Vector{x * rhs, y * rhs};
}

Vector Vector::operator/(int rhs) const {
    return Vector{x / rhs, y / rhs};
}

void Vector::operator+=(const Vector &rhs) {
    x += rhs.x;
    y += rhs.y;
}

void Vector::operator-=(const Vector &rhs) {
    x -= rhs.x;
    y -= rhs.y;
}

void Vector::operator*=(const Vector &rhs) {
    x *= rhs.x;
    y *= rhs.y;
}

void Vector::operator/=(const Vector &rhs) {
    x /= rhs.x;
    y /= rhs.y;
}

void Vector::operator+=(int rhs) {
    x += rhs;
    y += rhs;
}

void Vector::operator-=(int rhs) {
    x -= rhs;
    y -= rhs;
}

void Vector::operator*=(int rhs) {
    x *= rhs;
    y *= rhs;
}

void Vector::operator/=(int rhs) {
    x /= rhs;
    y /= rhs;
}
