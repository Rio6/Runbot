#include <SDL2/SDL.h>

#include "graphic.hpp"
#include "main.hpp"

int main(int argc, char *argv[]) {
    Graphic graphic;

    for(SDL_Event e; e.type != SDL_QUIT; SDL_PollEvent(&e)) {
        int frameStart = SDL_GetTicks();

        // Stuff here
        
        int frameTicks = SDL_GetTicks() - frameStart;
        if(frameTicks > config::TPF) continue;
        SDL_Delay(config::TPF - frameTicks);

        // Render
        graphic.draw();
    }

    return 0;
}
