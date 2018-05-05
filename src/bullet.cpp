/*
 * Author: Rio
 * Date: 2018/01/08
 */

#include "SDL2/SDL.h"

#include "bullet.hpp"
#include "object.hpp"
#include "game.hpp"
#include "collision.hpp"
#include "vector.hpp"

using runbot::Bullet;

Bullet::Bullet(Game *game, Vector<int> pos, float baseSpeed, bool enemy) :
    Object(pos, {baseSpeed + (enemy ? -1 : 1) * Bullet::SPEED, 0},
            {.minPos=pos, .maxPos=pos + Vector<int>{Bullet::W, Bullet::H}}),
    game(game), anim(0, 0, 40, 8, 1, 1, false), enemy(enemy) {

    Graphic::instance().playSound("bullet.wav");
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

    dead = pos.x > game->distance + Game::W || pos.x + Bullet::W < game->distance;
}

bool Bullet::onCollide(Object &other, Direction dir) {
    Graphic::instance().playSound("explosion.wav");
    dead = true;
    return true;
}

bool Bullet::isDead() {
    return dead;
}

bool Bullet::isEnemy() {
    return enemy;
}

runbot::Object::Type Bullet::getType() {
    return BULLET;
}
