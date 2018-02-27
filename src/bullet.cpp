/*
 * Author: Rio
 * Date: 2018/01/08
 */

#include "SDL.h"

#include "bullet.hpp"
#include "object.hpp"
#include "game.hpp"
#include "collision.hpp"
#include "vector.hpp"

using runbot::Bullet;

Bullet::Bullet(Game *game, Vector<int> pos, int baseSpeed) :
    Object(pos, {baseSpeed + Bullet::SPEED, 0}, {.minPos=pos, .maxPos=pos + Vector<int>{Bullet::W, Bullet::H}}),
    game(game), anim(0, 0, 40, 8, 1, 1, false) {
}

void Bullet::draw() {
    SDL_Rect src = anim.getCurrentClip();
    SDL_Rect des = {pos.x - game->distance, pos.y - game->cameraY, Bullet::W, Bullet::H};
    Graphic::instance().renderImage("bullet.png", &src, &des);
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
