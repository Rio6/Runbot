/*
 * Author: Rio
 * Date: 2017/05/21
 */

#include <vector>

#include "SDL.h"
#include "anim.hpp"

using runbot::Animation;

Animation::Animation(int x, int y, int w, int h, int length, int count, bool repeat = true) :
    length(length), repeat(repeat), spriteClips(count) {

    if(length <= 0) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Length is %d, setting to 1", length);
        this->length = 1;
    }

    for(int i = 0; i < (signed) spriteClips.size(); i++) {
        spriteClips[i] = {i * w + x, y, w, h};
    }
}

SDL_Rect Animation::getCurrentClip() {
    if(spriteClips.size() > 0)
        return spriteClips[frame];

    SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Sprite might not be initialized");
    return SDL_Rect();
}

int Animation::getLength() {
    return length;
}

void Animation::setLength(int length) {
    this->length = length;
}

void Animation::pause() {
    paused = true;
}

void Animation::start() {
    paused = false;
}

void Animation::doTick() {

    if(!paused && spriteClips.size() > 0) {
        while(length / (float) spriteClips.size() * frame < tick) {
            frame++;
        }

        if(repeat) {
            frame %= spriteClips.size();
        } else if(frame >= spriteClips.size()) {
            frame = 0;
            paused = true;
        }

        tick++;
        tick %= length;
    }
}
