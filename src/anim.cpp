/*
 * Author: Rio
 * Date: 2017/06/10
 */

#include <vector>

#include "SDL2/SDL.h"
#include "anim.hpp"
#include "main.hpp"

using runbot::Animation;

Animation::Animation(int x, int y, int w, int h, int aniLength, bool repeat = true) :
    x(x), y(y), w(w), h(h), aniLength(aniLength), repeat(repeat), spriteClips(0) {
}

Animation::~Animation() {
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

    logError("getCurrentClip", "sprite might not be initialized");
    return SDL_Rect();
}

int Animation::getLength() {
    return aniLength;
}

void Animation::setLength(int length) {
    aniLength = length;
}

void Animation::pause() {
    paused = true;
}

void Animation::start() {
    paused = false;
}

void Animation::doTick() {

    if(!paused && spriteClips.size() > 0) {
        while(aniLength / (float) spriteClips.size() * frame < tick) {
            frame++;
        }

        if(repeat) {
            frame %= spriteClips.size();
        } else if(frame >= spriteClips.size()) {
            frame = 0;
            paused = true;
        }

        tick++;
        tick %= aniLength;
    }
}
