#include "graphic.hpp"

using namespace graphic;

Graphic::Graphic() {
}

Graphic::~Graphic() {
}

int Graphic::init() {

    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("SDL init failed: %s", SDL_GetError());
        return 1;
    }
}
