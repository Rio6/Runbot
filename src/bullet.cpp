/*
 * Author: Rio
 * Date: 2018/1/8
 */

#include "SDL2/SDL.h"

#include "bullet.hpp"
#include "object.hpp"
#include "game.hpp"
#include "vector.hpp"

using runbot::Bullet;

Bullet::Bullet(Game *game, Vector<int> pos) :
    Object(pos, {Bullet::SPEED, 0}, {.minPos=pos + Vector<int>{5, 0}, .maxPos=pos + Vector<int>{Bullet::W - 5, Bullet::H}}),
    game(game), anim(0, 0, 40, 8, 1, false) {

    anim.createClips(1);
}

Bullet::~Bullet() {
}

void Bullet::draw() {
    SDL_Rect src = anim.getCurrentClip();
    SDL_Rect des = {pos.x - game->distance, pos.y, Bullet::W, Bullet::H};
    Graphic::instance().renderImage(BULLET_IMG, &src, &des);
}

void Bullet::doTick(int tick) {
    pos += speed;
}

bool Bullet::isDead(int distance) {
    return pos.x + Bullet::W - distance < 0;
}

runbot::Object::Type Bullet::getType() {
    return BULLET;
}
