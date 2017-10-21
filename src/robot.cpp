/*
 * Author: Rio
 * Date: 2017/10/10
 */

#include <stdexcept>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "robot.hpp"
#include "game.hpp"
#include "collision.hpp"
#include "anim.hpp"

using runbot::Robot;

Robot::Robot(SDL_Renderer *rend) :
    Object({0, 0}, {{20, 0}, {Robot::W - 40, Robot::H}}),
    bodyAnim(0, 0, 200, 400, 30, true),
    armAnim(0, 400, 200, 400, 30, false) {

    SDL_Surface *loadSurface = IMG_Load("assets/robot.png");
    if(loadSurface == NULL)
        throw std::runtime_error(IMG_GetError());

    sprite = SDL_CreateTextureFromSurface(rend, loadSurface);
    if(sprite == NULL) {
        SDL_FreeSurface(loadSurface);
        throw std::runtime_error(SDL_GetError());
    }

    bodyAnim.createClips(loadSurface->w / 200);
    armAnim.createClips(loadSurface->w / 200);

    SDL_FreeSurface(loadSurface);
}

Robot::~Robot() {
    SDL_DestroyTexture(sprite);
}

void Robot::draw(SDL_Renderer *rend, SDL_Texture *text, int distance) {
    SDL_Rect src, des;

    // Body animation
    src = bodyAnim.getCurrentClip();
    des = {10, pos.y, Robot::W, Robot::H};
    SDL_RenderCopy(rend, sprite, &src, &des);

    // Arm animation
    src = armAnim.getCurrentClip();
    des = {10, pos.y, Robot::W, Robot::H};
    SDL_RenderCopy(rend, sprite, &src, &des);
}

void Robot::doTick(int tick, int distance) {

    speed.x = pos.x - distance;
    pos.x = distance;

    pos.y -= speed.y;

    speed.y -= 1;

    hitbox.minPos = pos + 20;
    hitbox.maxPos = pos + Vector{Robot::W - 40, Robot::H};

    if(shootCD > 0)
        shootCD--;

    bodyAnim.doTick();
    armAnim.doTick();
}

void Robot::onCollide(Direction dir) {
    if(dir == DOWN) {
        bodyAnim.start();
        onGround = true;
    }
}

void Robot::jump(int force) {
    if(jumpReleased && force > 0 && onGround) {
        speed.y = force;
        jumpReleased = false;
        onGround = false;
        bodyAnim.pause();
    }
}

void Robot::releaseJump() {
    if(onGround)
        jumpReleased = true;
    else
        speed.y -= 2;
}

void Robot::shoot() {
    if(shootCD == 0) {
        armAnim.start();
        shootCD = armAnim.getLength();
    }
}
