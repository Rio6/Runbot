/*
 * Author: Rio
 * Date: 2017/12/12
 */

#include <stdexcept>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "tile.hpp"
#include "game.hpp"
#include "graphic.hpp"

using runbot::Tile;

Tile::Tile(Game *game, int x, int y, TileType type) :
    Object({x, y}, {.minPos={x, y}, .maxPos={x + Tile::W, y + Tile::H}}),
    game(game),
    anim(0, 0, 100, 100, 1, false), type(type) {

    anim.createClips(1);
}

Tile::~Tile() {
}

void Tile::draw() {
    SDL_Rect src, des;

    src = anim.getCurrentClip();
    des = {pos.x - game->distance, pos.y, Tile::W, Tile::H};
    Graphic::instance().renderImage(TILE_IMG, &src, &des);
}

bool Tile::isOut(int distance) {
    return pos.x + Tile::W - distance < 0;
}

