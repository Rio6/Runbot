/*
 * Author: Rio
 * Date: 2017/05/22
 */

#include <vector>

#include "anim.hpp"

using runbot::Animation;

Animation::Animation(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {
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

void Animation::nextFrame() {
    frame += 1;
    if(frame >= (signed) spriteClips.size())
        frame = 0;
}
