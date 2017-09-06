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
            SDL_Texture *getSprite();
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

            int y;
            int jumpForce;
            int shootCD;
            bool jumpReleased;
    };
};

#endif
