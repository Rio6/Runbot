/*
 * Author: Rio
 * Date: 2017/05/28
 */

#include <stdexcept>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "robot.hpp"
#include "game.hpp"
#include "graphic.hpp"
#include "anim.hpp"

using runbot::Robot;

Robot::Robot(Graphic &graphic) :
    anim(0, 0, Robot::W, Robot::H, 30) {

    SDL_Surface *loadSurface = IMG_Load("assets/robot.png");
    if(loadSurface == NULL)
        throw std::runtime_error(IMG_GetError());

    sprite = SDL_CreateTextureFromSurface(graphic.getRenderer(), loadSurface);
    if(sprite == NULL) {
        SDL_FreeSurface(loadSurface);
        throw std::runtime_error(SDL_GetError());
    }

    anim.createClips(loadSurface->w / Robot::W);

    SDL_FreeSurface(loadSurface);
}

Robot::~Robot() {
    SDL_DestroyTexture(sprite);
}

SDL_Texture *Robot::getSprite() {
    return sprite;
}

void Robot::draw(SDL_Renderer *rend, SDL_Texture *text) {
    SDL_Rect src = anim.getCurrentClip();
    SDL_Rect des = {10, y, Robot::W, Robot::H};
    SDL_RenderCopy(rend, getSprite(), &src, &des);
}

void Robot::doTick() {

    if(y + Robot::H < GAME_H) {
        jumpForce -= 2;
    } else if(y + Robot::H > GAME_H) {
        jumpForce = 0;
        y = GAME_H - Robot::H;
        anim.resume();
    }

    y -= jumpForce;

    anim.doTick();
}

// Jump with `force` force
void Robot::jump(int force) {
    if(force > 0 && y + Robot::H == GAME_H) {
        jumpForce = force;
        anim.pause();
    } else if(force < jumpForce && y + Robot::H < GAME_H) {
        jumpForce = force;
    }
}
