/*
 * Author: Rio
 * Date: 2017/05/22
 */

#ifndef _ANIM_H_
#define _ANIM_H_

#include <vector>
#include "SDL2/SDL.h"
#include "graphic.hpp"

namespace runbot {
    class Animation {
        public:
            Animation(int, int, int, int);
            ~Animation();
            void createClips(int);
            SDL_Rect getCurrentClip();
            void nextFrame();

        private:
            int frame;
            int x, y, w, h; // Start pint, size
            std::vector<SDL_Rect> spriteClips;
    };
};

#endif
