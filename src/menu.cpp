/*
 * Author: Rio
 * Date: 2018/02/11
 */

#include "menu.hpp"
#include "game.hpp"
#include "graphic.hpp"

using runbot::StartMenu;
using runbot::PauseMenu;

StartMenu::StartMenu(Game *game) : game(game),
    startBtn{Game::W / 2 - 200, Game::H / 2 - 50, 400, 100} {
}

void StartMenu::onClick(Vector<int> &pos) {
    if(pos.x > startBtn.x && pos.x < startBtn.x + startBtn.w &&
            pos.y > startBtn.y && pos.y < startBtn.y + startBtn.h) {

        game->startGame();
    }
}

void StartMenu::draw() {
    Graphic &graphic = Graphic::instance();

    SDL_Rect src = {0, 0, 1024, 575};
    SDL_Rect des = {0, 0, Game::W, Game::H};
    graphic.renderImage(MENU_IMG, &src, &des);

    src = {0, 0, 800, 400};
    graphic.renderImage("robot.png", &src, &startBtn);
}

PauseMenu::PauseMenu(Game *game) {
}

void PauseMenu::onClick(Vector<int> &pos) {
}

void PauseMenu::draw() {
}
