/*
 * Author: Rio
 * Date: 2017/06/10
 */

#include <SDL2/SDL.h>

#include "main.hpp"
#include "game.hpp"

int main(int argc, char *argv[]) {

    runbot::Game game;
    game.loop();

    return 0;
}

void runbot::logError(const char *msg, const char* err) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s: %s", msg, err);
}
