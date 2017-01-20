#include <SDL2/SDL.h>

#include "game.hpp"
#include "graphic.hpp"
#include "main.hpp"

int main(int argc, char *argv[]) {
    Game game;

    game.loop();

    return 0;
}
