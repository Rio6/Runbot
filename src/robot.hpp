/*
 * Author: Rio
 * Date: 2017/05/22
 */

#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "SDL2/SDL.h"

#include "graphic.hpp"
#include "anim.hpp"

namespace runbot {
    class Robot {
        private:
            SDL_Texture *sprite;
            Animation anim;

        public:
            static const int w = 200;
            static const int h = 400;
            Robot(Graphic &graphic);
            ~Robot();
            SDL_Texture *getSprite();
            Animation &getAnimaion();
            void doTick();
    };
};

#endif
