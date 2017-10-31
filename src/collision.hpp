/*
 * Author: Rio
 * Date: 2017/10/31
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
            static const int STEP_HEIGHT = 20;

            Collision(const Hitbox&, const Hitbox&);
            Direction getDirection();
            void solve(Object&, Object&);
        private:
            Vector overlap;
    };
};

#endif
