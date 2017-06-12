/*
 * Author: Rio
 * Date: 2017/06/11
 */

#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "SDL2/SDL.h"
#include "anim.hpp"

namespace runbot {

    typedef enum {
        LEFT,
        RIGHT
    } Direction;

    class Robot {
        public:
            static const int W = 200;
            static const int H = 400;

            Robot(SDL_Renderer*);
            ~Robot();
            void draw(SDL_Renderer*, SDL_Texture*);
            void doTick();

            // Actions
            void move(Direction);
            void stop();
            void jump();
            void releaseJump();
            void shoot();

        private:
            static const int SPEED = 10;
            static const int JUMP_FORCE = 20;

            SDL_Texture *sprite;
            Animation bodyAnim;
            Animation armAnim;
            Direction dir;

            int x, y;
            int xSpeed, ySpeed;
            int shootCD;
    };
};

#endif
