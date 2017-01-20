#include <SDL2/SDL.h>

#include "game.hpp"
#include "graphic.hpp"
#include "main.hpp"

Game::Game() {
    graphic.init();
}

Game::~Game() {}


void Game::loop() {

    running = true;
    while(running) {
        int frameStart = SDL_GetTicks();

        // Stuff here
        processEvents();
        
        int frameTicks = SDL_GetTicks() - frameStart;
        if(frameTicks > config::TPF) continue;
        SDL_Delay(config::TPF - frameTicks);

        // Render
        graphic.draw();
    }
}

void Game::processEvents() {

    SDL_Event eve;
    while(SDL_PollEvent(&eve)) {
        switch(eve.type) {
            case SDL_QUIT:
                running = false;
                break;
        }
    }
}
