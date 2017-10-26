/*
 * Author: Rio
 * Date: 2017/10/23
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
            runbot::Game::W, runbot::Game::H,
            SDL_WINDOW_FULLSCREEN_DESKTOP);
    if(win == NULL)
        throw std::runtime_error(SDL_GetError());

    rend = SDL_CreateRenderer(win, -1,
            SDL_RENDERER_ACCELERATED
#ifdef USE_VSYNC
            | SDL_RENDERER_PRESENTVSYNC
#endif
            );
    if(rend == NULL)
        throw std::runtime_error(SDL_GetError());

    // Configure the renderer
    SDL_RenderSetLogicalSize(rend, Game::W, Game::H);
    SDL_SetRenderDrawColor(rend, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(rend);
}

Graphic::~Graphic() {

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);

    rend = NULL;
    win = NULL;

    IMG_Quit();
    SDL_Quit();
}

SDL_Renderer *Graphic::getRenderer() {
    return rend;
}
