#include <SDL2/SDL.h>

#include "game.hpp"
#include "graphic.hpp"
#include "main.hpp"

void logError(const char *msg, const char* err) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s: %s", msg, err);
}

int main(int argc, char *argv[]) {

    Game game;
    game.loop();

    return 0;
}
