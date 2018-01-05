/*
 * Author: Rio
 * Date: 2018/1/3
 */

#include "SDL2/SDL.h"

#include "missile.hpp"
#include "object.hpp"
#include "game.hpp"

using runbot::Missile;

Missile::Missile(Game *game, int x, int y) :
    Object({x, y}, {.minPos={10, 5}, .maxPos={Missile::W - 10, Missile::H - 5}}),
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

    anim.doTick();
}

bool Missile::isOut(int distance) {
    return pos.x + Missile::W - distance < 0;
}

runbot::Object::Type Missile::getType() {
    return MISSILE;
}
