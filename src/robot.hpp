/*
 * Author: Rio
 * Date: 2017/05/21
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
            void draw();
            void doTick(int);
            bool onCollide(Object&, Direction);
            bool isDead();
            Type getType();
            void reset();
            int getHP();

            // Actions
            void jump();
            void releaseJump();
            void shoot();
            void die();

        private:
            Game *game;
            Animation bodyAnim;
            Animation armAnim;

            int shootCD = 0;
            int hp = 3;
            bool onGround = false;
            bool dead = false;
    };
};

#endif
