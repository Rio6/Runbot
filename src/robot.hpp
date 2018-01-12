/*
 * Author: Rio
 * Date: 2018/1/11
 */

#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "SDL2/SDL.h"
#include "object.hpp"
#include "collision.hpp"
#include "anim.hpp"

namespace runbot {
    class Game; //Forward declare

    class Robot : public Object {
        public:
            static const int W = 100;
            static const int H = 200;
            static const int JUMP_FORCE = 25;

            Robot(Game*);
            ~Robot();
            void draw();
            void doTick(int);
            bool onCollide(Object&, Direction dir);
            bool isDead();
            Type getType();

            // Actions
            void jump();
            void releaseJump();
            void shoot();
            void die();

        private:
            SDL_Texture *sprite;
            Game *game;
            Animation bodyAnim;
            Animation armAnim;

            int shootCD = 0;
            bool jumpReleased = false;
            bool onGround = false;
    };
};

#endif
