#include <SDL2/SDL.h>

#include "graphic.hpp"
#include "main.hpp"

int main(int argc, char *argv[]) {
    Graphic graphic;
    for(SDL_Event e; e.type != SDL_QUIT; SDL_PollEvent(&e));

    return 0;
}
