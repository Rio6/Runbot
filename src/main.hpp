/*
 * Author: Rio
 * Date: 2017/05/21
 */

#ifndef _MAIN_H_
#define _MAIN_H_

#include "SDL2/SDL.h"
#include "game.hpp"

namespace runbot {
    const int GAME_W = 640;
    const int GAME_H = 480;
    const char *const NAME = "Runbot";
    const int FPS = 30;
    const int TPF = 1000 / FPS; // ticks per frame

    extern Game game;

    void logError(const char *msg, const char* err);
};

#endif
