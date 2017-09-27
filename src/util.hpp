#ifndef _UTIL_H_
#define _UTIL_H_

namespace runbot {

    struct Vector {
        int x = 0, y = 0;
    };
    struct Hitbox {
        Vector pos;
        Vector oldPos;
        Vector size;
    };
};

#endif
