/*
 * Author: Rio
 * Date: 2018/02/11
 */

#include <cstdio>

#include "SDL.h"

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

    graphic.renderText("RUNBOT", &TITLE_RECT, 0);
    graphic.renderText("PLAY", &START_BTN, 0);
}


const SDL_Rect PauseMenu::TITLE_RECT = {Game::W / 2 - 125, 200, 250, 80};
const SDL_Rect PauseMenu::RESUME_BTN = {Game::W / 2 - 120, Game::H / 2, 130, 50};
const SDL_Rect PauseMenu::MENU_BTN = {Game::W / 2 + 40, Game::H / 2, 130, 50};

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

    graphic.renderText("PAUSED", &TITLE_RECT, 0);
    graphic.renderText("RESUME", &RESUME_BTN, 0);
    graphic.renderText("MENU", &MENU_BTN, 0);
}


const SDL_Rect DeadMenu::TITLE_RECT = {Game::W / 2 - 125, 200, 250, 80};
const SDL_Rect DeadMenu::RESTART_BTN = {Game::W / 2 - 160, Game::H / 2, 140, 50};
const SDL_Rect DeadMenu::MENU_BTN = {Game::W / 2 + 20, Game::H / 2, 140, 50};
const SDL_Rect DeadMenu::DIST_RECT = {Game::W / 2 - 100, Game::H / 2 + 50, 200, 40};

DeadMenu::DeadMenu(Game *game, int distance) : game(game), distance(distance) {
}

void DeadMenu::onClick(Vector<int> &pos) {
    if(inRect(RESTART_BTN, pos)) {
        game->setState(Game::RUNNING);
    } else if(inRect(MENU_BTN, pos)) {
        game->setState(Game::START);
    }
}

void DeadMenu::draw() {
    Graphic &graphic = Graphic::instance();

    graphic.renderText("GAME OVER", &TITLE_RECT, 0);
    graphic.renderText("RESTART", &RESTART_BTN, 0);
    graphic.renderText("MENU", &MENU_BTN, 0);

    char distDisplay[32];
    std::sprintf(distDisplay, "Distance:%5d", distance / 10);
    graphic.renderText(distDisplay, &DIST_RECT, 0);
}

const SDL_Rect GameMenu::PAUSE_BTN = {10, 10, 40, 40};

GameMenu::GameMenu(Game *game) : game(game) {
}

void GameMenu::onClick(Vector<int> &pos) {
    if(inRect(PAUSE_BTN, pos)) {
        game->setState(Game::PAUSED);
    }
}

void GameMenu::draw() {
    SDL_Rect src = {0, 0, 20, 20};
    Graphic::instance().renderImage("pause.png", &src, &PAUSE_BTN);
}
