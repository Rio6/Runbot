/*
 * Author: Rio
 * Date: 2017/10/23
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

            Robot(Game*, SDL_Renderer*);
            ~Robot();
            void draw(SDL_Renderer*);
            void doTick(int);
            void onCollide(Direction dir);
            bool isOut(int);

            // Actions
            void jump(int);
            void releaseJump();
            void shoot();

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
