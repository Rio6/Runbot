/*
 * Author: Rio
 * Date: 2018/1/8
 */

#ifndef _BULLET_H_
#define _BULLET_H_

#include "SDL2/SDL.h"
#include "object.hpp"
#include "anim.hpp"

namespace runbot {
    class Game; //Forward declare

    class Bullet : public Object {
        public:

            static const int W = 40;
            static const int H = 8;
            static constexpr float SPEED = 20;

            Bullet(Game*, Vector<int>);
            ~Bullet();
            void draw();
            void doTick(int);
            bool isDead(int);
            Type getType();

        private:
            Game *game;
            Animation anim;
    };
};

#endif

