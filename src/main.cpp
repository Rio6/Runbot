/*
 * Author: Rio
 * Date: 2017/11/29
 */

#include <SDL2/SDL.h>

#include "game.hpp"

int main(int argc, char *argv[]) {

    runbot::Game game;
    game.loop();

    return 0;
}
