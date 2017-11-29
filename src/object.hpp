/*
 * Author: Rio
 * Date: 2017/11/29
 */

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "SDL2/SDL.h"
#include "vector.hpp"
#include "collision.hpp"

namespace runbot {
    class Object {
        public:
            Object(Vector<int>);
            Object(Vector<int>, Hitbox);
            virtual ~Object() = default;
            virtual void draw() = 0;
            virtual void doTick(int);
            virtual void onCollide(Direction);
            virtual Vector<int> getPos();
            virtual Vector<float> getSpeed();
            virtual void setPos(Vector<int>);
            virtual void setSpeed(Vector<float>);
            virtual Hitbox &getHitbox();
            virtual bool isOut(int);
        protected:
            Vector<int> pos;
            Vector<float> speed;
            Hitbox hitbox;
    };
};

#endif
