/*
 * Author: Rio
 * Date: 2018/1/9
 */

#include "SDL2/SDL.h"

#include "missile.hpp"
#include "object.hpp"
#include "game.hpp"
#include "vector.hpp"
#include "collision.hpp"

using runbot::Missile;

Missile::Missile(Game *game, Vector<int> pos) :
    Object(pos, {.minPos={10, 5}, .maxPos={Missile::W - 10, Missile::H - 5}}),
    game(game), anim(0, 0, 120, 60, 10, true) {

    anim.createClips(2);
    anim.start();
}

Missile::~Missile() {
}

void Missile::draw() {
    SDL_Rect src = anim.getCurrentClip();
    SDL_Rect des = {pos.x - game->distance, pos.y, Missile::W, Missile::H};
    Graphic::instance().renderImage(MISSILE_IMG, &src, &des);
}

void Missile::doTick(int tick) {
    if(game->distance + Game::W >= pos.x) {
        speed = {-game->speed, 0};
    }

    pos += speed;

    hitbox.speed = speed;
    hitbox.minPos = pos + 20;
    hitbox.maxPos = pos + Vector<int>{Missile::W - 10, Missile::H - 5};

    dead = pos.x + Missile::W - game->distance < 0;

    anim.doTick();
}

bool Missile::onCollide(Object &other, Direction dir) {
    switch(other.getType()) {
        case ROBOT:
        case BULLET:
            dead = true;
            break;
        default:
            break;
    }
    return false;
}

bool Missile::isDead(int distance) {
    return dead;
}

runbot::Object::Type Missile::getType() {
    return MISSILE;
}
