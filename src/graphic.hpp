/*
 * Wrapper for SDL functions
 *
 * Author: Rio
 * Date: 2017/05/21
 */

#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_

#include <string>
#include <map>

#include "SDL2/SDL.h"

namespace runbot {

    // Class graphics
    class Graphic {
        public:
            static Graphic &instance();
            static void reset();

            SDL_Renderer *getRenderer();
            void renderImage(const std::string &name,
                    const SDL_Rect* src, const SDL_Rect* des, int color = 0xffffff);
            void renderText(const std::string &text, const SDL_Rect *des, int color = 0x000000);
            void clear();
            void update();

        private:
            static Graphic *graphic;

            SDL_Renderer *rend;
            SDL_Window *win;

            Graphic();
            ~Graphic();

            std::map<char, SDL_Rect> letters;
    };
};

#endif
