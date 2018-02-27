/*
 * Author: Rio
 * Date: 2018/02/25
 */

#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "object.hpp"
#include "anim.hpp"
#include "vector.hpp"

namespace runbot {
    class Game; // Forward declare

    class Explosion : public Object {
        public:
            Explosion(Game*, Vector<int> pos, Vector<int> size);
            void draw();
            void doTick(int);
            bool isDead();
            Type getType();
        private:
            int life = 8;
            Game *game;
            Animation anim;
            Vector<int> size;
    };
};

#endif
