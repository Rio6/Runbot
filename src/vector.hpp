/*
 * Author: Rio
 * Date: 2017/10/05
 */

#ifndef _VECTOR_H_
#define _VECTOR_H_

namespace runbot {
    struct Vector {
        int x = 0, y = 0;

        Vector operator+(const Vector&);
        Vector operator-(const Vector&);
        Vector operator*(const Vector&);
        Vector operator/(const Vector&);
        Vector operator+(int);
        Vector operator-(int);
        Vector operator*(int);
        Vector operator/(int);
    };
};

#endif
