/*
 * Author: Rio
 * Date: 2017/10/05
 */

#ifndef _VECTOR_H_
#define _VECTOR_H_

namespace runbot {

    template <typename T>
    struct Vector {
        T x = 0, y = 0;

        template<typename F>
        Vector &operator=(Vector<F>);

        template<typename F>
        Vector operator+(const Vector<F>&) const;
        template<typename F>
        Vector operator-(const Vector<F>&) const;
        template<typename F>
        Vector operator*(const Vector<F>&) const;
        template<typename F>
        Vector operator/(const Vector<F>&) const;

        template<typename F>
        Vector operator+(F) const;
        template<typename F>
        Vector operator-(F) const;
        template<typename F>
        Vector operator*(F) const;
        template<typename F>
        Vector operator/(F) const;

        template<typename F>
        void operator+=(const Vector<F>&);
        template<typename F>
        void operator-=(const Vector<F>&);
        template<typename F>
        void operator*=(const Vector<F>&);
        template<typename F>
        void operator/=(const Vector<F>&);

        template<typename F>
        void operator+=(F);
        template<typename F>
        void operator-=(F);
        template<typename F>
        void operator*=(F);
        template<typename F>
        void operator/=(F);
    };
};

#include "vector.tpp"

#endif
