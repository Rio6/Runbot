/*
 * Author: Rio
 * Date: 2018/05/04
 */

#ifndef _SHOOTER_H_
#define _SHOOTER_H_

#include "object.hpp"
#include "anim.hpp"

namespace runbot {
    class Game; //Forward declare

    class Shooter : public Object {
        public:
            static const int W = 100;
            static const int H = 150;
            static const int SCORE = 500;

            Shooter(Game*, Vector<int> pos);
            void draw();
            void doTick(int);
            bool onCollide(Object&, Direction);
            bool isDead();
            Type getType();

        private:
            static const float SPEED_FACTOR;

            Game *game;
            Animation bodyAnim;
            Animation armAnim;
            bool dead = false;
            int hp = 5;
            int spawnTime = 0;
    };
};

#endif
