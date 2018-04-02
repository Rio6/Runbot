/*
 * Author: Rio
 * Date: 2017/05/21
 */

#include <cstdlib>
#include <ctime>
#include "SDL2/SDL.h"

#include "game.hpp"
#include "graphic.hpp"

int main(int argc, char *argv[]) {

    // Seed random
    std::srand(std::time(0));

    // Log everything
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_INFO);

    // Start game
    runbot::Game game;
    game.loop();

    // Cleanup graphic stuff
    runbot::Graphic::reset();

    return 0;
}
