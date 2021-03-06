/*
 * Author: Rio
 * Date: 2017/12/08
 */

#include "SDL.h"

#include "background.hpp"
#include "graphic.hpp"
#include "game.hpp"

using runbot::Background;

Background::Background() : pos(0) {}

void Background::doTick(float gameSpeed) {
    pos += (int) (gameSpeed / 5);
    pos %= Background::W;
}

void Background::draw() {
    Graphic &graphic = Graphic::instance();
    SDL_Rect src, des;

    int edge = Game::W - pos * Game::W / Background::W;

    src = {pos, 0, Background::W - pos, Background::H};
    des = {0, 0, edge, Game::H};
    graphic.renderImage("bg.png", &src, &des);
    src = {0, 0, pos, Background::H};
    des = {edge, 0, Game::W - edge, Game::H};
    graphic.renderImage("bg.png", &src, &des);
}
