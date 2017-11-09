/*
 * Author: Rio
 * Date: 2017/11/02
 */

using runbot::Vector;

template<typename T>
template<typename F>
Vector<T> &Vector<T>::operator=(Vector<F> rhs) {
    x = rhs.x;
    y = rhs.y;

    return *this;
}

template<typename T>
template<typename F>
Vector<T> Vector<T>::operator+(const Vector<F> &rhs) const {
    return Vector<T>{x + rhs.x, y + rhs.y};
}

template<typename T>
template<typename F>
Vector<T> Vector<T>::operator-(const Vector<F> &rhs) const {
    return Vector<T>{x - rhs.x, y - rhs.y};
}

template<typename T>
template<typename F>
Vector<T> Vector<T>::operator*(const Vector<F> &rhs) const {
    return Vector<T>{x * rhs.x, y * rhs.y};
}

template<typename T>
template<typename F>
Vector<T> Vector<T>::operator/(const Vector<F> &rhs) const {
    return Vector<T>{x / rhs.x, y / rhs.y};
}

template<typename T>
template<typename F>
Vector<T> Vector<T>::operator+(F rhs) const {
    return Vector<T>{x + rhs, y + rhs};
}

template<typename T>
template<typename F>
Vector<T> Vector<T>::operator-(F rhs) const {
    return Vector<T>{x - rhs, y - rhs};
}

template<typename T>
template<typename F>
Vector<T> Vector<T>::operator*(F rhs) const {
    return Vector<T>{x * rhs, y * rhs};
}

template<typename T>
template<typename F>
Vector<T> Vector<T>::operator/(F rhs) const {
    return Vector<T>{x / rhs, y / rhs};
}

template<typename T>
template<typename F>
void Vector<T>::operator+=(const Vector<F> &rhs) {
    x += rhs.x;
    y += rhs.y;
}

template<typename T>
template<typename F>
void Vector<T>::operator-=(const Vector<F> &rhs) {
    x -= rhs.x;
    y -= rhs.y;
}

template<typename T>
template<typename F>
void Vector<T>::operator*=(const Vector<F> &rhs) {
    x *= rhs.x;
    y *= rhs.y;
}

template<typename T>
template<typename F>
void Vector<T>::operator/=(const Vector<F> &rhs) {
    x /= rhs.x;
    y /= rhs.y;
}

template<typename T>
template<typename F>
void Vector<T>::operator+=(F rhs) {
    x += rhs;
    y += rhs;
}

template<typename T>
template<typename F>
void Vector<T>::operator-=(F rhs) {
    x -= rhs;
    y -= rhs;
}

template<typename T>
template<typename F>
void Vector<T>::operator*=(F rhs) {
    x *= rhs;
    y *= rhs;
}

template<typename T>
template<typename F>
void Vector<T>::operator/=(F rhs) {
    x /= rhs;
    y /= rhs;
}
