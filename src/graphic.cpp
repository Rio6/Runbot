/*
 * Author: Rio
 * Date: 2017/05/28
 */

#include <stdexcept>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "graphic.hpp"
#include "game.hpp"

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
            //SDL_RENDERER_PRESENTVSYNC |
            SDL_RENDERER_TARGETTEXTURE);
    if(rend == NULL)
        throw std::runtime_error(SDL_GetError());

    rendBuff = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
            GAME_W, GAME_H);
    if(rendBuff == NULL)
        throw std::runtime_error(SDL_GetError());

    // Configure the renderer
    SDL_SetRenderDrawColor(rend, 0xff, 0xff, 0xff, 0xff);
    SDL_SetRenderTarget(rend, rendBuff);
    SDL_RenderClear(rend);
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

SDL_Texture *Graphic::getGameTexture() {
    return rendBuff;
}

void Graphic::drawToWindow() {
    // Set render target to default target (window)
    SDL_SetRenderTarget(rend, NULL);
    SDL_RenderCopy(rend, rendBuff, NULL, NULL);
    SDL_RenderPresent(rend);

    // Set render target back to the buffer texture
    SDL_SetRenderTarget(rend, rendBuff);
    SDL_RenderClear(rend);
}
