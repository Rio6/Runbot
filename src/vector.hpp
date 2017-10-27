/*
 * Author: Rio
 * Date: 2017/10/27
 */

#ifndef _VECTOR_H_
#define _VECTOR_H_

namespace runbot {
    struct Vector {
        int x = 0, y = 0;

        Vector operator+(const Vector&) const;
        Vector operator-(const Vector&) const;
        Vector operator*(const Vector&) const;
        Vector operator/(const Vector&) const;

        Vector operator+(int) const;
        Vector operator-(int) const;
        Vector operator*(int) const;
        Vector operator/(int) const;

        void operator+=(const Vector&);
        void operator-=(const Vector&);
        void operator*=(const Vector&);
        void operator/=(const Vector&);

        void operator+=(int);
        void operator-=(int);
        void operator*=(int);
        void operator/=(int);
    };
};

#endif
