/*
 * Author: Rio
 * Date: 2017/09/20
 */

#include <stdexcept>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "robot.hpp"
#include "game.hpp"
#include "anim.hpp"

using runbot::Robot;

Robot::Robot(SDL_Renderer *rend) :
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

void Robot::draw(SDL_Renderer *rend, SDL_Texture *text) {
    SDL_Rect src, des;

    // Body animation
    src = bodyAnim.getCurrentClip();
    des = {10, y, Robot::W, Robot::H};
    SDL_RenderCopy(rend, sprite, &src, &des);

    // Arm animation
    src = armAnim.getCurrentClip();
    des = {10, y, Robot::W, Robot::H};
    SDL_RenderCopy(rend, sprite, &src, &des);
}

void Robot::doTick(int tick, int distance) {

    y -= jumpForce;
    if(y + Robot::H > GAME_H) {
        jumpForce = 0;
        y = GAME_H - Robot::H;
        bodyAnim.start();
    } else {
        jumpForce -= 1;
    }

    if(shootCD > 0)
        shootCD--;

    bodyAnim.doTick();
    armAnim.doTick();
}

int Robot::getX() {
    return x;
}

int Robot::getY() {
    return y;
}

void Robot::jump(int force) {
    if(jumpReleased && force > 0 && y + Robot::H == GAME_H) {
        jumpForce = force;
        jumpReleased = false;
        bodyAnim.pause();
    }
}

void Robot::releaseJump() {
    jumpForce -= 2;
    jumpReleased = true;
}

void Robot::shoot() {
    if(shootCD == 0) {
        armAnim.start();
        shootCD = armAnim.getLength();
    }
}
