/*
 * Author: Rio
 * Date: 2017/10/05
 */

#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "vector.hpp"

namespace runbot {
    struct Hitbox {
        Vector pos;
        Vector size;

        bool collide(const Hitbox&);
    };
    class Collision {
        public:
            Collision(Hitbox, Hitbox);
            bool isColliding();
            void solve();
        private:
            Hitbox a, b;
            bool collide;
    };
};

#endif
