/*
 * Author: Rio
 * Date: 2018/02/11
 */

#include "SDL2/SDL.h"

#include "menu.hpp"
#include "game.hpp"
#include "graphic.hpp"

using namespace runbot;

bool Menu::inRect(const SDL_Rect &rect, const Vector<int> &pos) {
    return pos.x > rect.x && pos.x < rect.x + rect.w &&
        pos.y > rect.y && pos.y < rect.y + rect.h;
}


const SDL_Rect StartMenu::TITLE_RECT = {Game::W / 2 - 300, 100, 600, 150};
const SDL_Rect StartMenu::START_BTN = {Game::W / 2 - 100, Game::H / 2, 200, 80};

StartMenu::StartMenu(Game *game) : game(game) {
}

void StartMenu::onClick(Vector<int> &pos) {
    if(inRect(START_BTN, pos)) {
        // Clicked on the button
        game->setState(Game::RUNNING);
    }
}

void StartMenu::draw() {
    Graphic &graphic = Graphic::instance();

    SDL_Rect src = {0, 0, 1024, 575};
    SDL_Rect des = {0, 0, Game::W, Game::H};
    graphic.renderImage("bg.png", &src, &des);

    graphic.renderText("RUNBOT", &TITLE_RECT);
    graphic.renderText("PLAY", &START_BTN);
}


const SDL_Rect PauseMenu::TITLE_RECT = {Game::W / 2 - 100, 130, 200, 50};
const SDL_Rect PauseMenu::RESUME_BTN = {Game::W / 2 - 120, Game::H / 2, 80, 40};
const SDL_Rect PauseMenu::MENU_BTN = {Game::W / 2 + 40, Game::H / 2, 80, 40};

PauseMenu::PauseMenu(Game *game) : game(game) {
}

void PauseMenu::onClick(Vector<int> &pos) {
    if(inRect(RESUME_BTN, pos)) {
        game->setState(Game::RUNNING);
    } else if(inRect(MENU_BTN, pos)) {
        game->setState(Game::START);
    }
}

void PauseMenu::draw() {
    Graphic &graphic = Graphic::instance();

    graphic.renderText("PAUSED", &TITLE_RECT);
    graphic.renderText("RESUME", &RESUME_BTN);
    graphic.renderText("MENU", &MENU_BTN);
}


const SDL_Rect DeadMenu::TITLE_RECT = {Game::W / 2 - 100, 130, 200, 50};
const SDL_Rect DeadMenu::MENU_BTN = {Game::W / 2 - 100, Game::H / 2, 200, 80};

DeadMenu::DeadMenu(Game *game) : game(game) {
}

void DeadMenu::onClick(Vector<int> &pos) {
    if(inRect(MENU_BTN, pos)) {
        game->setState(Game::START);
    }
}

void DeadMenu::draw() {
    Graphic &graphic = Graphic::instance();

    graphic.renderText("GAME OVER", &TITLE_RECT);
    graphic.renderText("MENU", &MENU_BTN);
}
