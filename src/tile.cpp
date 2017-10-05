/*
 * Author: Rio
 * Date: 2017/10/03
 */

#include <stdexcept>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "tile.hpp"

using runbot::Tile;

SDL_Texture *Tile::sprite;

Tile::Tile(SDL_Renderer *rend, int x, int y, TileType type) :
    Object({x, y}, {{x, y}, {Tile::W, Tile::H}}), anim(0, 0, 100, 100, 1, false), type(type) {

        if(sprite == NULL) {
            SDL_Surface *loadSurface = IMG_Load("assets/tiles.png");
            if(loadSurface == NULL)
                throw std::runtime_error(IMG_GetError());

            sprite = SDL_CreateTextureFromSurface(rend, loadSurface);
            SDL_FreeSurface(loadSurface);

            if(sprite == NULL) {
                throw std::runtime_error(SDL_GetError());
            }
        }

    anim.createClips(1);
}

Tile::~Tile() {
}

void Tile::draw(SDL_Renderer *rend, SDL_Texture *text, int distance) {
    SDL_Rect src, des;

    src = anim.getCurrentClip();
    des = {pos.x - distance, pos.y, Tile::W, Tile::H};
    SDL_RenderCopy(rend, sprite, &src, &des);
}

void Tile::freeSprite() {
    // Sprite is static, so free it from Game
    SDL_DestroyTexture(sprite);
}
