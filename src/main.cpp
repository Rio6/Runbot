/*
 * Author: Rio
 * Date: 2017/05/21
 */

#include <SDL2/SDL.h>

#include "game.hpp"
#include "graphic.hpp"
#include "main.hpp"

using namespace runbot;

Game runbot::game;

int main(int argc, char *argv[]) {

    game.loop();

    return 0;
}

void runbot::logError(const char *msg, const char* err) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s: %s", msg, err);
}
