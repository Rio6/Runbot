/*
 * Author: Rio
 * Date: 2017/10/03
 */

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "SDL2/SDL.h"
#include "vector.hpp"
#include "collision.hpp"

namespace runbot {
    class Object {
        public:
            Object(Vector);
            Object(Vector, Hitbox);
            virtual ~Object() = default;
            virtual void draw(SDL_Renderer*, SDL_Texture*, int) = 0;
            virtual void doTick(int, int);
            virtual void onCollide(Direction);
            virtual Vector getPos();
            virtual Vector getSpeed();
            virtual void setPos(Vector);
            virtual void setSpeed(Vector);
            virtual Hitbox getHitbox();
            virtual bool isOut(int);
        protected:
            Vector pos;
            Vector speed = {0, 0};
            Hitbox hitbox;
    };
};

#endif
