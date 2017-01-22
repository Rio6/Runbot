#include <iostream>

#include "graphic.hpp"
#include "main.hpp"

Graphic::Graphic() {

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        throw std::runtime_error(SDL_GetError());

    win = SDL_CreateWindow(config::NAME,
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            config::WIN_W, config::WIN_H,
            SDL_WINDOW_FULLSCREEN);
    if(win == NULL)
        throw std::runtime_error(SDL_GetError());

    rend = SDL_CreateRenderer(win, -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(rend == NULL)
        throw std::runtime_error(SDL_GetError());
}

Graphic::~Graphic() {

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);

    rend = NULL;
    win = NULL;

    SDL_Quit();
}

void Graphic::draw() {
    SDL_SetRenderDrawColor(rend, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(rend);
    SDL_RenderPresent(rend);
}
