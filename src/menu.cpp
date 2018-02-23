/*
 * Author: Rio
 * Date: 2018/02/11
 */

#include "SDL2/SDL.h"

#include "menu.hpp"
#include "game.hpp"
#include "graphic.hpp"

using runbot::StartMenu;
using runbot::PauseMenu;

StartMenu::StartMenu(Game *game) : game(game),
    startBtn{(Game::W - BTN_W) / 2, Game::H - BTN_H * 2, BTN_W, BTN_H} {
}

void StartMenu::onClick(Vector<int> &pos) {
    if(pos.x > startBtn.x && pos.x < startBtn.x + startBtn.w &&
            pos.y > startBtn.y && pos.y < startBtn.y + startBtn.h) {
        // Clicked on the button

        game->setState(Game::RUNNING);
    }
}

void StartMenu::draw() {
    Graphic &graphic = Graphic::instance();

    SDL_Rect src = {0, 0, 1024, 575};
    SDL_Rect des = {0, 0, Game::W, Game::H};
    graphic.renderImage(BG_IMG, &src, &des);

    des = {Game::W / 2 - 300, 100, 600, 150};
    graphic.renderText("RUNBOT", &des);
    graphic.renderText("PLAY", &startBtn);
}

PauseMenu::PauseMenu(Game *game) : game(game),
    resumeBtn{(Game::W - BTN_W * 3) / 2, Game::H / 2, BTN_W, BTN_H},
    quitBtn{(Game::W + BTN_W) / 2, Game::H / 2, BTN_W, BTN_H} {
}

void PauseMenu::onClick(Vector<int> &pos) {
}

void PauseMenu::draw() {
    Graphic &graphic = Graphic::instance();

    graphic.renderText("RESUME", &resumeBtn);
    graphic.renderText("QUIT", &quitBtn);
}
