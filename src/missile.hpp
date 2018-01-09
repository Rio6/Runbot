/*
 * Author: Rio
 * Date: 2018/1/8
 */

#ifndef _MISSILE_H_
#define _MISSILE_H_

#include "SDL2/SDL.h"
#include "object.hpp"
#include "anim.hpp"
#include "vector.hpp"

namespace runbot {
    class Game; //Forward declare

    class Missile : public Object {
        public:

            static const int W = 120;
            static const int H = 60;

            Missile(Game*, Vector<int>);
            ~Missile();
            void draw();
            void doTick(int);
            bool isOut(int);
            Type getType();

        private:
            Game *game;
            Animation anim;
    };
};

#endif


