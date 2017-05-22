/*
 * Author: Rio
 * Date: 2017/05/21
 */

#include <iostream>
#include <vector>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "anim.hpp"
#include "graphic.hpp"

using runbot::Animation;

Animation::Animation(Graphic &graphic,
        const char *path, int x, int y, int w, int h) : spriteClips(0) {

    SDL_Surface *loadSurface = IMG_Load(path);
    if(loadSurface == NULL) 
        throw std::runtime_error(IMG_GetError());

    sprite = SDL_CreateTextureFromSurface(graphic.getRenderer(),
            loadSurface);

    crntFrame = 0;

    spriteClips.resize(loadSurface->w / w);

    for(int i = 0; i < (signed) spriteClips.capacity(); i++) {
        spriteClips[i] = {i * w + x, y, w, h};
    }

    SDL_FreeSurface(loadSurface);
    loadSurface = NULL;
}


Animation::~Animation() {
    SDL_DestroyTexture(sprite);
}

SDL_Texture *Animation::getSprite() {
    return sprite;
}

SDL_Rect Animation::getSpriteClip() {
    return spriteClips[crntFrame];
}

void Animation::nextFrame() {
    crntFrame += 1;
    if(crntFrame >= (signed) spriteClips.size())
        crntFrame = 0;
}
