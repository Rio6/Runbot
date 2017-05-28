/*
 * Author: Rio
 * Date: 2017/05/21
 */

#include <SDL2/SDL.h>

#include "game.hpp"
#include "main.hpp"

using namespace runbot;

Game runbot::game;

int main(int argc, char *argv[]) {

    game.loop();

    return 0;
}
