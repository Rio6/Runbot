/*
 * Author: Rio
 * Date: 2017/05/22
 */

#include <stdexcept>

#include "SDL2/SDL.h"

#include "game.hpp"
#include "graphic.hpp"
#include "robot.hpp"

using runbot::Game;

Game::Game() try : graphic(), robot(graphic) {
} catch (std::runtime_error exc) {
    logError("Failed to initilize", exc.what());
}

Game::~Game() {}


void Game::loop() {

    running = true;
    while(running) {
        int frameStart = SDL_GetTicks();

        // Stuff here
        processEvents();

        robot.doTick();
        
        int frameTicks = SDL_GetTicks() - frameStart;
        if(frameTicks > runbot::TPF) continue;
        SDL_Delay(runbot::TPF - frameTicks);

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

void runbot::logError(const char *msg, const char* err) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s: %s", msg, err);
}
