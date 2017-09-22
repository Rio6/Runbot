/*
 * Author: Rio
 * Date: 2017/06/10
 */

#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "SDL2/SDL.h"
#include "object.hpp"
#include "anim.hpp"

namespace runbot {
    class Robot : public Object {
        public:
            static const int W = 100;
            static const int H = 200;

            Robot(SDL_Renderer*);
            ~Robot();
            void draw(SDL_Renderer*, SDL_Texture*);
            void doTick(int, int);
            int getX();
            int getY();

            // Actions
            void jump(int);
            void releaseJump();
            void shoot();

        private:
            SDL_Texture *sprite;
            Animation bodyAnim;
            Animation armAnim;

            int x, y;
            int jumpForce = 0;
            int shootCD = 0;
            bool jumpReleased = false;
    };
};

#endif
