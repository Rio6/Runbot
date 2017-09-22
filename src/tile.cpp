/*
 * Author: Rio
 * Date: 2017/09/20
 */

#include <stdexcept>
#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "tile.hpp"

using runbot::Tile;

SDL_Texture *Tile::sprite;

Tile::Tile(SDL_Renderer *rend, int x, int y, TileType type) :
    anim(0, 0, 100, 100, 1, false), type(type), x(x), y(y) {

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

void Tile::draw(SDL_Renderer *rend, SDL_Texture *text) {
    SDL_Rect src, des;

    src = anim.getCurrentClip();
    des = {x - distance, y, Tile::W, Tile::H};
    SDL_RenderCopy(rend, sprite, &src, &des);
}

void Tile::doTick(int tick, int distance) {
    this->distance = distance;
}

int Tile::getX() {
    return x;
}

int Tile::getY() {
    return y;
}

void Tile::freeSprite() {
    // Sprite is static, so free it from Game
    SDL_DestroyTexture(sprite);
}
