/*
 * Author: Rio
 * Date: 2017/06/10
 */

#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "SDL2/SDL.h"
#include "anim.hpp"

namespace runbot {
    class Robot {
        public:
            static const int W = 200;
            static const int H = 400;

            Robot(SDL_Renderer*);
            ~Robot();
            void draw(SDL_Renderer*, SDL_Texture*);
            void doTick();

            // Actions
            void jump(int);
            void releaseJump();
            void shoot();

        private:
            SDL_Texture *sprite;
            Animation bodyAnim;
            Animation armAnim;

            int y = 0;
            int jumpForce = 0;
            int shootCD = 0;
            bool jumpReleased = false;
    };
};

#endif
