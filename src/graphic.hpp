/*
 * Author: Rio
 * Date: 2017/10/23
 */

#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_

#define USE_VSYNC

#include "SDL2/SDL.h"

namespace runbot {
    class Graphic {
        public:
            Graphic();
            ~Graphic();
            SDL_Renderer *getRenderer();

        private:
            SDL_Renderer *rend;
            SDL_Window *win;
    };
};

#endif
