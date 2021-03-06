/*
 * Author: Rio
 * Date: 2018/01/03
 */

#include "SDL.h"
#include "SDL_mixer.h"

#include "missile.hpp"
#include "object.hpp"
#include "game.hpp"
#include "vector.hpp"
#include "collision.hpp"
#include "explosion.hpp"
#include "bullet.hpp"
#include "media.hpp"

using runbot::Missile;

int Missile::soundCh = -1;
int Missile::missileCount = 0;

Missile::Missile(Game *game, Vector<int> pos) :
    Object(pos, {-game->speed, 0}, {
            .minPos = pos + Vector<int>{10, 0},
            .maxPos = pos + Vector<int>{Missile::W, Missile::H},
            }),
    game(game), anim(0, 0, 120, 60, 10, 2, true) {

    anim.start();
}

Missile::~Missile() {
    if(active) {
        if(missileCount == 1) {
            if(!dead && pos.x < game->distance + Game::W) // Not dead && was in screen
                Mix_FadeOutChannel(soundCh, 1000);
            else
                Mix_HaltChannel(soundCh);
            soundCh = -1;
        }
        missileCount--; // Only count missiles that are making sounds
    }
}

void Missile::draw() {
    SDL_Rect src = anim.getCurrentClip();
    SDL_Rect des = {pos.x - game->distance, pos.y - game->cameraY, Missile::W, Missile::H};
    Graphic::instance().renderImage("missile.png", &src, &des);
}

void Missile::doTick(int tick) {

    // Play the missile sound
    if(soundCh < 0) {
        soundCh = Mix_FadeInChannel(-1, Media::get<Mix_Chunk*>("missile.wav"), -1, 1000);
    }

    if(!active) {
        missileCount++; // Only count missiles that are making sounds
        active = true;
    }

    pos += speed;

    hitbox.speed = speed;
    hitbox.minPos = pos + Vector<int>{10, 0};
    hitbox.maxPos = pos + Vector<int>{Missile::W, Missile::H};

    anim.doTick();
}

bool Missile::onCollide(Object &other, Direction dir) {
    bool dying = false;
    bool push = false;
    switch(other.getType()) {
        case ROBOT:
            dying = true;
            push = true;
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
    return push;
}

bool Missile::isDead() {
    return dead || pos.x + Missile::W - game->distance < 0;
}

runbot::Object::Type Missile::getType() {
    return MISSILE;
}
