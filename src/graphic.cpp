/*
 * Author: Rio
 * Date: 2017/11/29
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
    if(win == nullptr)
        throw std::runtime_error(SDL_GetError());

    rend = SDL_CreateRenderer(win, -1,
            SDL_RENDERER_ACCELERATED
#ifdef USE_VSYNC
            | SDL_RENDERER_PRESENTVSYNC
#endif
            );
    if(rend == nullptr)
        throw std::runtime_error(SDL_GetError());

    // Configure the renderer
    SDL_RenderSetLogicalSize(rend, Game::W, Game::H);
    SDL_SetRenderDrawColor(rend, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(rend);

    loadImages();
}

Graphic::~Graphic() {

    for(auto &img : imgs) {
        SDL_DestroyTexture(img.second);
        img.second = nullptr;
    }

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);

    rend = nullptr;
    win = nullptr;

    IMG_Quit();
    SDL_Quit();
}

Graphic &Graphic::instance() {
    static Graphic graphic;
    return graphic;
}

void Graphic::renderImage(const std::string &name,
        const SDL_Rect *src, const SDL_Rect *des) {
    try {
        SDL_Texture *text = imgs.at(name);
        SDL_RenderCopy(rend, text, src, des);
    } catch(std::out_of_range e) {
        SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Cannot render %s: %s", name.c_str(), e.what());
    }
}

void Graphic::clear() {
    SDL_RenderClear(rend);
}

void Graphic::update() {
    SDL_RenderPresent(rend);
}

void Graphic::loadImages() {

    for(auto &img : imgs) {
        SDL_Surface *loadSurface = IMG_Load(("assets/" + img.first).c_str());
        if(loadSurface == nullptr) {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Cannot load %s: %s", img.first.c_str(), IMG_GetError());
            continue;
        }

        img.second = SDL_CreateTextureFromSurface(rend, loadSurface);
        if(img.second == nullptr)
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Cannot load %s: %s", img.first.c_str(), SDL_GetError());

        SDL_FreeSurface(loadSurface);
    }
}
