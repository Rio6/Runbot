/*
 * Author: Rio
 * Date: 2017/05/21
 */

#include <cstdlib>
#include <ctime>
#include "SDL.h"

#include "game.hpp"

int main(int argc, char *argv[]) {

    // Seed random
    std::srand(std::time(0));

    runbot::Game game;
    game.loop();

    return 0;
}
