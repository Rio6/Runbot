/*
 * Calculates SDL_Rect of sprites for a spritesheet
 * Does not store/care about the actual image
 *
 * Author: Rio
 * Date: 2017/05/21
 */

#ifndef _ANIM_H_
#define _ANIM_H_

#include <vector>
#include "SDL.h"

namespace runbot {
    class Animation {
        public:
            Animation(int x, int y, int w, int h, int length, int count, bool repeat);

            SDL_Rect getCurrentClip();
            void setLength(int);
            int getLength();

            void pause();
            void start();
            void doTick();

        private:
            int length; // The length of the animation
            unsigned int frame = 0;
            unsigned int tick = 0;
            bool paused = true;
            bool repeat;
            std::vector<SDL_Rect> spriteClips;
    };
};

#endif
