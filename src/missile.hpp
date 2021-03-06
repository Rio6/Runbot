/*
 * Author: Rio
 * Date: 2018/01/03
 */

#ifndef _MISSILE_H_
#define _MISSILE_H_

#include "SDL.h"
#include "object.hpp"
#include "anim.hpp"
#include "vector.hpp"
#include "collision.hpp"

namespace runbot {
    class Game; //Forward declare

    class Missile : public Object {
        public:

            static const int W = 120;
            static const int H = 60;
            static const int SCORE = 50;

            Missile(Game*, Vector<int> pos);
            ~Missile();
            void draw();
            void doTick(int);
            bool onCollide(Object&, Direction);
            bool isDead();
            Type getType();

        private:
            // Only use 1 channel for all missiles
            static int soundCh;
            static int missileCount;

            Game *game;
            Animation anim;
            bool dead = false;
            bool active = false;
    };
};

#endif


