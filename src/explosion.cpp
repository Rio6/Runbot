/*
 * Author: Rio
 * Date: 2018/02/25
 */

#include "SDL2/SDL.h"

#include "explosion.hpp"
#include "object.hpp"
#include "anim.hpp"
#include "vector.hpp"
#include "graphic.hpp"
#include "game.hpp"

using runbot::Explosion;

Explosion::Explosion(Game *game, Vector<int> pos, Vector<int> size) :
    Object(pos), game(game),
    anim(0, 0, 100, 100, life, 5, false), size(size) {

    anim.start();
}

void Explosion::draw() {
    SDL_Rect src = anim.getCurrentClip();
    SDL_Rect des = {pos.x - game->distance, pos.y - game->cameraY, size.x, size.y};
    Graphic::instance().renderImage("explosion.png", &src, &des);
}

void Explosion::doTick(int tick) {
    if(--life > 0)
        anim.doTick();
}

bool Explosion::isDead() {
    return life <= 0;
}

runbot::Object::Type Explosion::getType() {
    return EXPLOSION;
}
