/*
 * Author: Rio
 * Date: 2017/05/21
 */

#ifndef _ANIM_H_
#define _ANIM_H_

#include <vector>

#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"

#include "graphic.hpp"

namespace runbot {
    class Animation {
        public:
            Animation(Graphic &graphic,
                    const char *path, int x, int y, int w, int h);
            ~Animation();
            SDL_Texture *getSprite();
            SDL_Rect getSpriteClip();
            void nextFrame();

        private:
            int crntFrame;
            SDL_Texture *sprite;
            std::vector<SDL_Rect> spriteClips;
    };
};

#endif
