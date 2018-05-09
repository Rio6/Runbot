/*
 * Author: Rio
 * Date: 2017/09/20
 */

#include <stdexcept>

#include "SDL.h"

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
    anim(0, 0, 100, 100, 1, 1, false), type(type) {
}

void Tile::draw() {
    SDL_Rect src, des;

    src = anim.getCurrentClip();
    des = {pos.x - game->distance, pos.y - game->cameraY, Tile::W, Tile::H};
    Graphic::instance().renderImage("tiles.png", &src, &des);
}

bool Tile::onCollide(Object &other, Direction dir) {
    return true;
}

bool Tile::isDead() {
    return pos.x + Tile::W - game->distance < 0;
}

runbot::Object::Type Tile::getType() {
    return TILE;
}
