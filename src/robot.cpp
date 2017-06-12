/*
 * Author: Rio
 * Date: 2017/06/11
 */

#include <stdexcept>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "robot.hpp"
#include "game.hpp"
#include "anim.hpp"

using runbot::Robot;

Robot::Robot(SDL_Renderer *rend) :
    bodyAnim(0, 0, Robot::W, Robot::H, SPEED * 3, true),
    armAnim(0, Robot::H, Robot::W, Robot::H, 30, false), dir(RIGHT),
    pos(), xSpeed(0), ySpeed(0), shootCD(0) {

    SDL_Surface *loadSurface = IMG_Load("assets/robot.png");
    if(loadSurface == NULL)
        throw std::runtime_error(IMG_GetError());

    sprite = SDL_CreateTextureFromSurface(rend, loadSurface);
    if(sprite == NULL) {
        SDL_FreeSurface(loadSurface);
        throw std::runtime_error(SDL_GetError());
    }

    bodyAnim.createClips(loadSurface->w / Robot::W);
    armAnim.createClips(loadSurface->w / Robot::W);

    SDL_FreeSurface(loadSurface);
}

Robot::~Robot() {
    SDL_DestroyTexture(sprite);
}

void Robot::draw(SDL_Renderer *rend, SDL_Texture *text) {
    SDL_Rect src, des;

    SDL_RendererFlip flip;
    switch(dir) {
        case LEFT:
            flip = SDL_FLIP_HORIZONTAL;
            break;
        case RIGHT:
        default:
            flip = SDL_FLIP_NONE;
            break;
    }

    // Body animation
    src = bodyAnim.getCurrentClip();
    des = {pos.x, pos.y, Robot::W, Robot::H};
    SDL_RenderCopyEx(rend, sprite, &src, &des, 0, NULL, flip);

    // Arm animation
    src = armAnim.getCurrentClip();
    des = {pos.x, pos.y, Robot::W, Robot::H};
    SDL_RenderCopyEx(rend, sprite, &src, &des, 0, NULL, flip);
}

void Robot::doTick() {

    if(pos.y + Robot::H < GAME_H) {
        ySpeed++;
    } else if(pos.y + Robot::H > GAME_H) {
        ySpeed = 0;
        pos.y = GAME_H - Robot::H;
    }
    pos.y += ySpeed;

    pos.x += xSpeed;

    if(shootCD > 0)
        shootCD--;

    bodyAnim.doTick();
    armAnim.doTick();
}

void Robot::move(Direction dir) {
    if(xSpeed == 0 || this->dir != dir) {
        switch(dir) {
            case LEFT:
                xSpeed = -SPEED;
                break;
            case RIGHT:
                xSpeed = SPEED;
                break;
        }

        this->dir = dir;
        bodyAnim.reset();
    }
    bodyAnim.start();
}

void Robot::stop() {
    xSpeed = 0;
    bodyAnim.reset();
}

void Robot::jump() {
    if(pos.y + Robot::H == GAME_H) {
        ySpeed = -JUMP_FORCE;
    }
}

void Robot::releaseJump() {
    if(pos.y + Robot::H < GAME_H) {
        ySpeed += JUMP_FORCE / 6;
    }
}

void Robot::shoot() {
    if(shootCD == 0) {
        armAnim.start();
        shootCD = armAnim.getLength();
    }
}
