/*
 * Author: Rio
 * Date: 2018/01/03
 */

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

#include "missile.hpp"
#include "object.hpp"
#include "game.hpp"
#include "vector.hpp"
#include "collision.hpp"
#include "explosion.hpp"
#include "bullet.hpp"
#include "media.hpp"

using runbot::Missile;

Missile::Missile(Game *game, Vector<int> pos) :
    Object(pos, {-game->speed, 0}, {
            .minPos = pos + Vector<int>{10, 0},
            .maxPos = pos + Vector<int>{Missile::W, Missile::H},
            }),
    game(game), anim(0, 0, 120, 60, 10, 2, true) {

    anim.start();
}

Missile::~Missile() {
    if(!dead && pos.x < game->distance + Game::W) // Not dead && was in screen
        Mix_FadeOutChannel(soundCh, 100);
    else
        Mix_HaltChannel(soundCh);
}

void Missile::draw() {
    SDL_Rect src = anim.getCurrentClip();
    SDL_Rect des = {pos.x - game->distance, pos.y - game->cameraY, Missile::W, Missile::H};
    Graphic::instance().renderImage("missile.png", &src, &des);
}

void Missile::doTick(int tick) {

    // Play the missile sound
    if(soundCh < 0) {
        soundCh = Mix_FadeInChannel(-1, Media::get<Mix_Chunk*>("missile.wav"), -1, 100);
    }

    pos += speed;

    hitbox.speed = speed;
    hitbox.minPos = pos + Vector<int>{10, 0};
    hitbox.maxPos = pos + Vector<int>{Missile::W, Missile::H};

    anim.doTick();
}

bool Missile::onCollide(Object &other, Direction dir) {
    bool dying = false;
    switch(other.getType()) {
        case ROBOT:
            dying = true;
            break;
        case BULLET:
            dying = !dynamic_cast<Bullet&>(other).isEnemy();
            break;
        default:
            break;
    }

    if(dying) {
        dead = true;
        game->addScore(Missile::SCORE);
        game->spawn(new Explosion(game, pos, {Missile::W, Missile::H}));
    }
    return false;
}

bool Missile::isDead() {
    return dead || pos.x + Missile::W - game->distance < 0;
}

runbot::Object::Type Missile::getType() {
    return MISSILE;
}
