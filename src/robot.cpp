/*
 * Author: Rio
 * Date: 2017/05/22
 */

#include <stdexcept>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "robot.hpp"
#include "graphic.hpp"
#include "anim.hpp"

using runbot::Robot;

Robot::Robot(Graphic &graphic) :
    anim(0, 0, Robot::w, Robot::h, 15) {

    SDL_Surface *loadSurface = IMG_Load("assets/robot.png");
    if(loadSurface == NULL)
        throw std::runtime_error(IMG_GetError());

    sprite = SDL_CreateTextureFromSurface(graphic.getRenderer(), loadSurface);
    if(sprite == NULL) {
        SDL_FreeSurface(loadSurface);
        throw std::runtime_error(SDL_GetError());
    }

    anim.createClips(loadSurface->w / Robot::w);

    SDL_FreeSurface(loadSurface);
}

Robot::~Robot() {
    SDL_DestroyTexture(sprite);
}

SDL_Texture *Robot::getSprite() {
    return sprite;
}

runbot::Animation &Robot::getAnimaion() {
    return anim;
}

void Robot::doTick() {
    anim.doTick();
}
