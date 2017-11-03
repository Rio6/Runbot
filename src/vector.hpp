/*
 * Author: Rio
 * Date: 2017/11/02
 */

#ifndef _VECTOR_H_
#define _VECTOR_H_

namespace runbot {

    template <typename T>
    struct Vector {
        T x = 0, y = 0;

        template<typename F>
        Vector &operator=(Vector<F> rhs) {
            x = rhs.x;
            y = rhs.y;

            return *this;
        }


        Vector operator+(const Vector&) const;
        Vector operator-(const Vector&) const;
        Vector operator*(const Vector&) const;
        Vector operator/(const Vector&) const;

        Vector operator+(T) const;
        Vector operator-(T) const;
        Vector operator*(T) const;
        Vector operator/(T) const;

        void operator+=(const Vector&);
        void operator-=(const Vector&);
        void operator*=(const Vector&);
        void operator/=(const Vector&);

        void operator+=(T);
        void operator-=(T);
        void operator*=(T);
        void operator/=(T);
    };
};

#endif
