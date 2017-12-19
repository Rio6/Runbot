/*
 * Author: Rio
 * Date: 2017/12/15
 */

#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "vector.hpp"

namespace runbot {
    class Object; // Forward declare

    struct Hitbox {
        Vector<int> minPos;
        Vector<int> maxPos;
        Vector<float> speed;
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
            Collision(Object*, Object*);
            void solve();
            bool operator<(const Collision&); // For std::sort
        private:
            Object *a, *b;
            Direction dir;
            Vector<int> normal;
            float time;
    };
};

#endif
