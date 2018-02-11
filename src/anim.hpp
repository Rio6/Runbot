/*
 * Author: Rio
 * Date: 2017/05/21
 */

#ifndef _ANIM_H_
#define _ANIM_H_

#include <vector>
#include "SDL2/SDL.h"

namespace runbot {
    class Animation {
        public:
            Animation(int x, int y, int w, int h, int length, bool repeat);

            // Call this to create the clips
            void createClips(int clipCount);
            // get current clip, return SDL_Rect{0, 0, 0, 0} if clip has size 0
            SDL_Rect getCurrentClip();
            void setLength(int);
            int getLength();

            void pause();
            void start();
            void doTick();

        private:
            int x, y, w, h; // Start pint, size
            int length; // The length of the animation
            unsigned int frame = 0;
            unsigned int tick = 0;
            bool paused = true;
            bool repeat;
            std::vector<SDL_Rect> spriteClips;
    };
};

#endif