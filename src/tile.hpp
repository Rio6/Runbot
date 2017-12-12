/*
 * Author: Rio
 * Date: 2017/12/12
 */

#ifndef _TILE_H_
#define _TILE_H_

#include "SDL2/SDL.h"
#include "object.hpp"
#include "anim.hpp"

namespace runbot {
    class Game; //Forward declare

    class Tile : public Object {
        public:

            enum TileType {
                TILE_GROUND
            };

            static const int W = 100;
            static const int H = 100;

            Tile(Game*, int, int, TileType);
            ~Tile();
            void draw();
            bool isOut(int);

        private:
            Game *game;
            Animation anim;
            TileType type;
    };
};

#endif
