/*
 * Author: Rio
 * Date: 2017/10/03
 */

#ifndef _UTIL_H_
#define _UTIL_H_

namespace runbot {

    struct Vector {
        int x = 0, y = 0;
    };
    struct Hitbox {
        Vector pos;
        Vector size;

        bool collide(const Hitbox&);
    };
};

#endif
