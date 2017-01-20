#include <iostream>

#include "graphic.hpp"
#include "main.hpp"

Graphic::Graphic() {
}

Graphic::~Graphic() {

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);

    rend = NULL;
    win = NULL;

    SDL_Quit();
}

int Graphic::init() {

    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        logError("Graphic::init()", SDL_GetError);
        return -1;
    }

    win = SDL_CreateWindow(config::NAME,
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            config::WIN_W, config::WIN_H,
            SDL_WINDOW_FULLSCREEN);
    if(win == NULL) {
        logError("Graphic::init()", SDL_GetError);
        return -1;
    }

    rend = SDL_CreateRenderer(win, -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(rend == NULL) {
        logError("Graphic::init()", SDL_GetError);
        return -1;
        throw std::runtime_error(SDL_GetError());
    }

    return 0;
}

void Graphic::draw() {
    SDL_SetRenderDrawColor(rend, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(rend);
    SDL_RenderPresent(rend);
}
