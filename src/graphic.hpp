/*
 * Author: Rio
 * Date: 2017/05/28
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
            SDL_Texture *getGameTexture();
            void drawToWindow();

        private:
            SDL_Renderer *rend;
            SDL_Texture *rendBuff;
            SDL_Window *win;
    };
};

#endif
