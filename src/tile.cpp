/*
 * Author: Rio
 * Date: 2018/1/11
 */

#include <stdexcept>

#include "SDL2/SDL.h"

#include "tile.hpp"
#include "object.hpp"
#include "game.hpp"
#include "graphic.hpp"
#include "vector.hpp"
#include "collision.hpp"

using runbot::Tile;

Tile::Tile(Game *game, Vector<int> pos, TileType type) :
    Object(pos, {.minPos=pos, .maxPos=pos + Vector<int>{Tile::W, Tile::H}}),
    game(game),
    anim(0, 0, 100, 100, 1, false), type(type) {

    anim.createClips(1);
}

void Tile::draw() {
    SDL_Rect src, des;

    src = anim.getCurrentClip();
    des = {pos.x - game->distance, pos.y, Tile::W, Tile::H};
    Graphic::instance().renderImage(TILE_IMG, &src, &des);
}

bool Tile::onCollide(Object &other, Direction dir) {
    return false;
}

bool Tile::isDead() {
    return pos.x + Tile::W - game->distance < 0;
}

runbot::Object::Type Tile::getType() {
    return TILE;
}
