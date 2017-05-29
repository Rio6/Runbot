/*
 * Author: Rio
 * Date: 2017/05/22
 */

#include <vector>

#include "anim.hpp"

using runbot::Animation;

Animation::Animation(int x, int y, int w, int h, int aniLength) :
    x(x), y(y), w(w), h(h), aniLength(aniLength), frame(0), tick(0) {
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
    return spriteClips[frame];
}

void Animation::pause() {
    paused = true;
}

void Animation::resume() {
    paused = false;
}

void Animation::doTick() {

    if(!paused) {
        while(aniLength / (float) spriteClips.size() * frame < tick) {
            frame++;
        }
        frame %= spriteClips.size();

        tick++;
        tick %= aniLength;
    }
}
