/*
 * Author: Rio
 * Date: 2018/01/08
 */

#include "SDL.h"
#include "SDL_mixer.h"

#include "bullet.hpp"
#include "object.hpp"
#include "game.hpp"
#include "collision.hpp"
#include "vector.hpp"
#include "media.hpp"

using runbot::Bullet;

Bullet::Bullet(Game *game, Vector<int> pos, float baseSpeed, bool enemy) :
    Object(pos, {baseSpeed + (enemy ? -1 : 1) * Bullet::SPEED, 0},
            {.minPos=pos, .maxPos=pos + Vector<int>{Bullet::W, Bullet::H}, .mass=.2}),
    game(game), anim(0, 0, 40, 8, 1, 1, false), enemy(enemy) {

    Mix_PlayChannel(-1, Media::get<Mix_Chunk*>("bullet.wav"), 0);
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
    bool dying = false;
    switch(other.getType()) {
        case ROBOT:
            dying = enemy;
            break;
        case TILE:
        case BULLET:
            dying = true;
            break;
        default:
            dying = !enemy;
    }

    if(dying) {
        Mix_PlayChannel(-1, Media::get<Mix_Chunk*>("bullet_hit.wav"), 0);
        dead = true;
    }
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
