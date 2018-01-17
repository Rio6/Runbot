/*
 * Author: Rio
 * Date: 2017/05/21
 */

#include <vector>

#include "SDL2/SDL.h"
#include "anim.hpp"

using runbot::Animation;

Animation::Animation(int x, int y, int w, int h, int length, bool repeat = true) :
    x(x), y(y), w(w), h(h), length(length), repeat(repeat), spriteClips(0) {
}

void Animation::createClips(int clipCount) {

    spriteClips.resize(clipCount);

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
    length = length;
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
