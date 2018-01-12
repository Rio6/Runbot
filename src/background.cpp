/*
 * Author: Rio
 * Date: 2017/12/08
 */

#include "SDL2/SDL.h"

#include "background.hpp"
#include "graphic.hpp"
#include "game.hpp"

using runbot::Background;

Background::Background() : pos(0) {}

void Background::doTick() {
    pos += 1;
    pos %= Background::W;
}

void Background::draw() {
    Graphic &graphic = Graphic::instance();
    SDL_Rect src, des;

    int edge = Game::W - pos * Game::W / Background::W;

    src = {pos, 0, Background::W - pos, Background::H};
    des = {0, 0, edge, Game::H};
    graphic.renderImage(BG_IMG, &src, &des);
    src = {0, 0, pos, Background::H};
    des = {edge, 0, Game::W - edge, Game::H};
    graphic.renderImage(BG_IMG, &src, &des);
}
