/*
 * Author: Rio
 * Date: 2017/10/05
 */

#ifndef _VECTOR_H_
#define _VECTOR_H_

namespace runbot {
    struct Vector {
        int x = 0, y = 0;

        Vector operator+(const Vector &lhs);
        Vector operator-(const Vector &lhs);
        Vector operator*(const Vector &lhs);
        Vector operator/(const Vector &lhs);
        Vector operator+(int lhs);
        Vector operator-(int lhs);
        Vector operator*(int lhs);
        Vector operator/(int lhs);
    };
};

#endif
