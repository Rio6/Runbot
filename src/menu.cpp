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

Menu::MenuRect::MenuRect(int x, int y, int w, int h) : SDL_Rect{x, y, w, h} {}

bool Menu::MenuRect::onMouse(Vector<int> &pos, bool down) {
    if(inRect(pos)) {
        if(down) {
            state = DOWN;
        } else {
            if(state == DOWN) {
                // mouse down and up -> clicked
                return true;
            }
            state = UP;
        }
    } else {
        state = UP;
    }
    return false;
}

bool Menu::MenuRect::inRect(const Vector<int> &pos) {
    return pos.x > x && pos.x < x + w && pos.y > y && pos.y < y + h;
}


StartMenu::StartMenu(Game *game) : game(game),
    titleRect{Game::W / 2 - 300, 100, 600, 150},
    startBtn{Game::W / 2 - 100, Game::H / 2, 200, 80} {}

void StartMenu::onMouse(Vector<int> &pos, bool down) {
    if(startBtn.onMouse(pos, down))
        game->setState(Game::RUNNING);
}

void StartMenu::draw() {
    Graphic &graphic = Graphic::instance();

    SDL_Rect des = {0, 0, Game::W, Game::H};
    graphic.renderImage("bg.png", nullptr, &des);

    graphic.renderText("RUNBOT", &titleRect, 0);
    // UP = 0; DOWN = 1; So state * color would be black when UP, the color when DOWN
    graphic.renderText("PLAY", &startBtn, startBtn.state * 0x00ff00);
}


PauseMenu::PauseMenu(Game *game) : game(game),
    bgRect{Game::W / 2 - 195, Game::H / 2 - 140, 410, 250},
    titleRect{Game::W / 2 - 110, 200, 250, 80},
    resumeBtn{Game::W / 2 - 120, Game::H / 2, 130, 50},
    menuBtn{Game::W / 2 + 40, Game::H / 2, 130, 50} {}

void PauseMenu::onMouse(Vector<int> &pos, bool down) {
    if(resumeBtn.onMouse(pos, down)) {
        game->setState(Game::RUNNING);
    } else if(menuBtn.onMouse(pos, down)) {
        game->setState(Game::START);
    }
}

void PauseMenu::draw() {
    Graphic &graphic = Graphic::instance();
    
    graphic.renderImage("menu.png", nullptr, &bgRect);
    graphic.renderText("PAUSED", &titleRect, 0);
    graphic.renderText("RESUME", &resumeBtn, resumeBtn.state * 0x00ff00);
    graphic.renderText("MENU", &menuBtn, menuBtn.state * 0x00ff00);
}


DeadMenu::DeadMenu(Game *game, int distance) : game(game), distance(distance),
    bgRect{Game::W / 2 - 220, Game::H / 2 - 160, 440, 355},
    titleRect{Game::W / 2 - 125, 200, 250, 80},
    restartBtn{Game::W / 2 - 160, Game::H / 2, 140, 50},
    menuBtn{Game::W / 2 + 20, Game::H / 2, 140, 50},
    distRect{Game::W / 2 - 100, Game::H / 2 + 80, 200, 40} {}

void DeadMenu::onMouse(Vector<int> &pos, bool down) {
    if(restartBtn.onMouse(pos, down)) {
        game->setState(Game::RUNNING);
    } else if(menuBtn.onMouse(pos, down)) {
        game->setState(Game::START);
    }
}

void DeadMenu::draw() {
    Graphic &graphic = Graphic::instance();

    graphic.renderImage("menu.png", nullptr, &bgRect);
    graphic.renderText("GAME OVER", &titleRect, 0);
    graphic.renderText("RESTART", &restartBtn, restartBtn.state * 0x00ff00);
    graphic.renderText("MENU", &menuBtn, menuBtn.state * 0x00ff00);

    char distDisplay[32];
    std::sprintf(distDisplay, "Distance:%5d", distance / 10);
    graphic.renderText(distDisplay, &distRect, 0);
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
