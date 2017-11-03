/*
 * Author: Rio
 * Date: 2017/11/02
 */

#include "vector.hpp"

using runbot::Vector;

template<typename T>
Vector<T> Vector<T>::operator+(const Vector<T> &rhs) const {
    return Vector<T>{x + rhs.x, y + rhs.y};
}

template<typename T>
Vector<T> Vector<T>::operator-(const Vector<T> &rhs) const {
    return Vector<T>{x - rhs.x, y - rhs.y};
}

template<typename T>
Vector<T> Vector<T>::operator*(const Vector<T> &rhs) const {
    return Vector<T>{x * rhs.x, y * rhs.y};
}

template<typename T>
Vector<T> Vector<T>::operator/(const Vector<T> &rhs) const {
    return Vector<T>{x / rhs.x, y / rhs.y};
}

template<typename T>
Vector<T> Vector<T>::operator+(T rhs) const {
    return Vector<T>{x + rhs, y + rhs};
}

template<typename T>
Vector<T> Vector<T>::operator-(T rhs) const {
    return Vector<T>{x - rhs, y - rhs};
}

template<typename T>
Vector<T> Vector<T>::operator*(T rhs) const {
    return Vector<T>{x * rhs, y * rhs};
}

template<typename T>
Vector<T> Vector<T>::operator/(T rhs) const {
    return Vector<T>{x / rhs, y / rhs};
}

template<typename T>
void Vector<T>::operator+=(const Vector<T> &rhs) {
    x += rhs.x;
    y += rhs.y;
}

template<typename T>
void Vector<T>::operator-=(const Vector<T> &rhs) {
    x -= rhs.x;
    y -= rhs.y;
}

template<typename T>
void Vector<T>::operator*=(const Vector<T> &rhs) {
    x *= rhs.x;
    y *= rhs.y;
}

template<typename T>
void Vector<T>::operator/=(const Vector<T> &rhs) {
    x /= rhs.x;
    y /= rhs.y;
}

template<typename T>
void Vector<T>::operator+=(T rhs) {
    x += rhs;
    y += rhs;
}

template<typename T>
void Vector<T>::operator-=(T rhs) {
    x -= rhs;
    y -= rhs;
}

template<typename T>
void Vector<T>::operator*=(T rhs) {
    x *= rhs;
    y *= rhs;
}

template<typename T>
void Vector<T>::operator/=(T rhs) {
    x /= rhs;
    y /= rhs;
}

template class Vector<int>;
template class Vector<float>;
