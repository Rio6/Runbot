/*
 * Author: Rio
 * Date: 2018/01/08
 */

#ifndef _BULLET_H_
#define _BULLET_H_

#include "SDL.h"
#include "object.hpp"
#include "anim.hpp"
#include "collision.hpp"

namespace runbot {
    class Game; //Forward declare

    class Bullet : public Object {
        public:

            static const int W = 40;
            static const int H = 8;
            static constexpr float SPEED = 15;

            Bullet(Game*, Vector<int>, int);
            void draw();
            void doTick(int);
            bool onCollide(Object&, Direction);
            bool isDead();
            Type getType();

        private:
            Game *game;
            Animation anim;
            bool dead = false;
    };
};

#endif


