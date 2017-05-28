/*
 * Author: Rio
 * Date: 2017/05/21
 */

#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_

#include "SDL2/SDL.h"

namespace runbot {
    class Graphic {
        public:
            Graphic();
            ~Graphic();
            SDL_Renderer *getRenderer();
            void draw();

        private:
            SDL_Renderer *rend;
            SDL_Texture *rendBuff;
            SDL_Window *win;
    };
};

#endif
