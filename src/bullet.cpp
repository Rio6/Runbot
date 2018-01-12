/*
 * Author: Rio
 * Date: 2018/1/12
 */

#include "SDL2/SDL.h"

#include "bullet.hpp"
#include "object.hpp"
#include "game.hpp"
#include "collision.hpp"
#include "vector.hpp"

using runbot::Bullet;

Bullet::Bullet(Game *game, Vector<int> pos, int baseSpeed) :
    Object(pos, {baseSpeed + Bullet::SPEED, 0}, {.minPos=pos, .maxPos=pos + Vector<int>{Bullet::W, Bullet::H}}),
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

    hitbox.speed = speed;
    hitbox.minPos = pos;
    hitbox.maxPos = pos + Vector<int>{Bullet::W, Bullet::H};

    dead = pos.x > game->distance + Game::W;
}

bool Bullet::onCollide(Object &other, Direction dir) {
    dead = true;
    return true;
}

bool Bullet::isDead() {
    return dead;
}

runbot::Object::Type Bullet::getType() {
    return BULLET;
}
