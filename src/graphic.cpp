/*
 * Author: Rio
 * Date: 2017/05/22
 */

#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "graphic.hpp"
#include "main.hpp"
#include "robot.hpp"
#include "anim.hpp"

using runbot::Graphic;

Graphic::Graphic() {

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        throw std::runtime_error(SDL_GetError());

    int imgFlags = IMG_INIT_PNG;
    if((IMG_Init(imgFlags) & imgFlags) != imgFlags)
        throw std::runtime_error(IMG_GetError());

    win = SDL_CreateWindow(runbot::NAME,
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            runbot::GAME_W, runbot::GAME_H,
            SDL_WINDOW_FULLSCREEN_DESKTOP);
    if(win == NULL)
        throw std::runtime_error(SDL_GetError());

    rend = SDL_CreateRenderer(win, -1,
            SDL_RENDERER_ACCELERATED |
            SDL_RENDERER_PRESENTVSYNC |
            SDL_RENDERER_TARGETTEXTURE);
    if(rend == NULL)
        throw std::runtime_error(SDL_GetError());

    rendBuff = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
            GAME_W, GAME_H);
    if(rendBuff == NULL)
        throw std::runtime_error(SDL_GetError());
}

Graphic::~Graphic() {

    SDL_DestroyTexture(rendBuff);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);

    rendBuff = NULL;
    rend = NULL;
    win = NULL;

    IMG_Quit();
    SDL_Quit();
}

SDL_Renderer *Graphic::getRenderer() {
    return rend;
}

void Graphic::draw() {
    SDL_SetRenderTarget(rend, rendBuff);
    SDL_SetRenderDrawColor(rend, 0xff, 0xff, 0xff, 0xff);

    SDL_RenderClear(rend);

    Animation &anim = game.robot.getAnimaion();
    SDL_Rect src = anim.getCurrentClip();
    SDL_Rect des = {0, 0, 100, 200};
    SDL_RenderCopy(rend, game.robot.getSprite(), &src, &des);

    SDL_SetRenderTarget(rend, NULL);
    SDL_RenderCopy(rend, rendBuff, NULL, NULL);
    SDL_RenderPresent(rend);
}
