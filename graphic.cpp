#include <iostream>

#include "graphic.hpp"
#include "main.hpp"

Graphic::Graphic() {

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        throw std::runtime_error(SDL_GetError());

    win = SDL_CreateWindow(config::TITLE.c_str(),
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            config::WIN_W, config::WIN_H,
            SDL_WINDOW_FULLSCREEN_DESKTOP);
    if(win == NULL)
        throw std::runtime_error(SDL_GetError());
}

Graphic::~Graphic() {
    SDL_DestroyWindow(win);
    SDL_Quit();
}
