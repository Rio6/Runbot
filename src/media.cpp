/*
 * Author: Rio
 * Date: 2017/06/23
 */

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

#include "media.hpp"
#include "graphic.hpp"

#include "config.h"

using runbot::Media;

Media *Media::media = nullptr;

Media::Media() {
    SDL_Renderer *rend = Graphic::instance().getRenderer();

    // Load textures
    for(auto &img : imgs) {
        SDL_Surface *loadSurface = IMG_Load((DATA_DIR + img.first).c_str());
        if(!loadSurface) {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Cannot load %s: %s", img.first.c_str(), IMG_GetError());
            continue;
        }

        img.second = SDL_CreateTextureFromSurface(rend, loadSurface);
        if(!img.second)
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Cannot load %s: %s", img.first.c_str(), SDL_GetError());

        SDL_FreeSurface(loadSurface);
    }

    // Load sounds
    for(auto &sound : sounds) {
        sound.second = Mix_LoadWAV((DATA_DIR + sound.first).c_str());
        if(!sound.second) {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Cannot load %s: %s", sound.first.c_str(), Mix_GetError());
        }
    }
}

Media::~Media() {

    for(auto &img : imgs) {
        SDL_DestroyTexture(img.second);
        img.second = nullptr;
    }

    for(auto &sound : sounds) {
        Mix_FreeChunk(sound.second);
        sound.second = nullptr;
    }
}

template<> SDL_Texture *Media::get<SDL_Texture*>(const std::string &name) {
    auto &imgs = Media::instance().imgs;
    if(imgs.count(name) > 0)
        return imgs.at(name);
    return nullptr;
}

template<> Mix_Chunk *Media::get<Mix_Chunk*>(const std::string &name) {
    auto &sounds = Media::instance().sounds;
    if(sounds.count(name) > 0)
        return sounds.at(name);
    return nullptr;
}

Media &Media::instance() {
    if(!media)
        media = new Media();
    return *media;
}

void Media::reset() {
    delete media;
    media = nullptr;
}
