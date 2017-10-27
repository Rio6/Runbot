/*
 * Author: Rio
 * Date: 2017/10/27
 */

#include <stdexcept>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "tile.hpp"
#include "game.hpp"

using runbot::Tile;

SDL_Texture *Tile::sprite;

Tile::Tile(Game *game, SDL_Renderer *rend, int x, int y, TileType type) :
    Object({x, y}, {.minPos={x, y}, .maxPos={x + Tile::W, y + Tile::H}}),
    game(game),
    anim(0, 0, 100, 100, 1, false), type(type) {

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

    hitbox.updateOldPos();
}

Tile::~Tile() {
}

void Tile::draw(SDL_Renderer *rend) {
    SDL_Rect src, des;

    src = anim.getCurrentClip();
    des = {pos.x - game->distance, pos.y, Tile::W, Tile::H};
    SDL_RenderCopy(rend, sprite, &src, &des);
}

bool Tile::isOut(int distance) {
    return pos.x + Tile::W - distance < 0;
}

void Tile::freeSprite() {
    // Sprite is static, so free it from Game
    SDL_DestroyTexture(sprite);
}
