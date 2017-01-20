#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_

#include <SDL2/SDL.h>

#include "graphic.hpp"

class Graphic {

    public:
        Graphic();
        ~Graphic();
        void draw();

    private:
        SDL_Renderer *rend;
        SDL_Texture *rendBuff
        SDL_Window *win;
};

#endif
