/*
 * Author: Rio
 * Date: 2017/09/22
 */

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "SDL.h"
#include "vector.hpp"
#include "collision.hpp"

namespace runbot {
    class Object {
        public:

            enum Type {
                UNKNOWN,
                ROBOT,
                TILE,
                MISSILE,
                BULLET,
                EXPLOSION
            };

            Object(Vector<int> pos);
            Object(Vector<int> pos, Hitbox);
            Object(Vector<int> pos, Vector<float> speed, Hitbox);
            virtual ~Object() = default;
            virtual void draw() = 0;
            virtual void doTick(int);
            virtual bool onCollide(Object&, Direction);
            virtual Vector<int> getPos();
            virtual Vector<float> getSpeed();
            virtual void setPos(Vector<int>);
            virtual void setSpeed(Vector<float>);
            virtual Hitbox &getHitbox();
            virtual bool isDead();
            virtual Type getType() = 0;
        protected:
            Vector<int> pos;
            Vector<float> speed;
            Hitbox hitbox;
    };
};

#endif
