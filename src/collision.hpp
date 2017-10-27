/*
 * Author: Rio
 * Date: 2017/10/27
 */

#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "vector.hpp"

namespace runbot {
    class Object; // Forward declare

    struct Hitbox {
        Vector minPos;
        Vector maxPos;
        Vector oldMinPos;
        Vector oldMaxPos;

        void updateOldPos();
    };

    enum Direction {
        NONE,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    Direction getOpposite(Direction);

    class Collision {
        public:
            Collision(const Hitbox&, const Hitbox&);
            Direction getDirection();
            void solve(Object&, Object&);
        private:
            Vector overlap;
    };
};

#endif
