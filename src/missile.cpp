/*
 * Author: Rio
 * Date: 2018/01/03
 */

#include "SDL2/SDL.h"

#include "missile.hpp"
#include "object.hpp"
#include "game.hpp"
#include "vector.hpp"
#include "collision.hpp"
#include "explosion.hpp"
#include "bullet.hpp"

using runbot::Missile;

Missile::Missile(Game *game, Vector<int> pos) :
    Object(pos, {-game->speed, 0}, {
            pos + Vector<int>{10, 0},
            pos + Vector<int>{Missile::W, Missile::H},
            speed}),
    game(game), anim(0, 0, 120, 60, 10, 2, true) {

    anim.start();
}

Missile::~Missile() {
    Graphic::instance().stopSound(soundCh);
    if(!dead && pos.x < game->distance + Game::W) // Not dead && was in screen
        Graphic::instance().playSound("missile_end.wav");
}

void Missile::draw() {
    SDL_Rect src = anim.getCurrentClip();
    SDL_Rect des = {pos.x - game->distance, pos.y - game->cameraY, Missile::W, Missile::H};
    Graphic::instance().renderImage("missile.png", &src, &des);
}

void Missile::doTick(int tick) {
    Graphic& graphic = Graphic::instance();

    // Play sound when inside the screen
    if(soundCh < 0 && game->distance + Game::W >= pos.x) {
        soundCh = graphic.playSound("missile_start.wav", 0);
    }

    // Play sound loop when start sound finished
    if(soundCh >= 0 && !graphic.soundPlaying(soundCh)) {
        graphic.playSound("missile.wav", -1, soundCh);
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
