/*
 * Author: Rio
 * Date: 2017/10/02
 */

#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "util.hpp"

namespace runbot {
    class Collision {
        public:
            Collision(Hitbox, Hitbox);
        private:
            Hitbox a, b;
    };
};

#endif
