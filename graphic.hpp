#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_

#include <SDL2/SDL.h>

class Graphic {

    public:
        Graphic();
        ~Graphic();

    private:
        SDL_Renderer *rend;
        SDL_Window *win;
};

#endif
