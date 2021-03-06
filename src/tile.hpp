/*
 * Author: Rio
 * Date: 2018/09/20
 */

#ifndef _TILE_H_
#define _TILE_H_

#include "SDL.h"
#include "object.hpp"
#include "anim.hpp"
#include "vector.hpp"
#include "collision.hpp"

namespace runbot {
    class Game; //Forward declare

    class Tile : public Object {
        public:

            static const int W = 100;
            static const int H = 100;

            Tile(Game*, Vector<int> pos);
            void draw();
            bool onCollide(Object&, Direction);
            bool isDead();
            Type getType();

        private:
            Game *game;
            Animation anim;
    };
};

#endif
