/*
 * Author: Rio
 * Date: 2017/09/26
 */

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "SDL2/SDL.h"
#include "util.hpp"

namespace runbot {
    class Object {
        public:
            Object(Vector);
            virtual ~Object() = default;
            virtual void draw(SDL_Renderer*, SDL_Texture*, int) = 0;
            virtual void doTick(int);
            virtual Vector getPos();
            virtual Vector getSpeed();
            virtual Hitbox getHitbox();
            virtual bool isOut(int);
        protected:
            Vector pos;
            Vector speed = {0, 0};
            Hitbox hitbox;
    };
};

#endif
