/*
 * Author: Rio
 * Date: 2018/1/8
 */

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "SDL2/SDL.h"
#include "vector.hpp"
#include "collision.hpp"

namespace runbot {
    class Object {
        public:

            enum Type {
                UNKNOWN,
                ROBOT,
                TILE,
                MISSILE
            };

            Object(Vector<int>);
            Object(Vector<int>, Hitbox);
            Object(Vector<int>, Vector<float>, Hitbox);
            virtual ~Object() = default;
            virtual void draw() = 0;
            virtual void doTick(int);
            virtual void onCollide(Object&, Direction);
            virtual Vector<int> getPos();
            virtual Vector<float> getSpeed();
            virtual void setPos(Vector<int>);
            virtual void setSpeed(Vector<float>);
            virtual Hitbox &getHitbox();
            virtual bool isOut(int);
            virtual Type getType() = 0;
        protected:
            Vector<int> pos;
            Vector<float> speed;
            Hitbox hitbox;
    };
};

#endif
