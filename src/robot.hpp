/*
 * Author: Rio
 * Date: 2017/05/28
 */

#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "SDL2/SDL.h"

#include "graphic.hpp"
#include "anim.hpp"

namespace runbot {
    class Robot {
        public:
            static const int W = 200;
            static const int H = 400;

            Robot(Graphic&);
            ~Robot();
            SDL_Texture *getSprite();
            void draw(SDL_Renderer*, SDL_Texture*);

            void jump(int);
            void doTick();

        private:
            SDL_Texture *sprite;
            Animation anim;
            int y;

            int jumpForce;
    };
};

#endif
