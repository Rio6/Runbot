/*
 * Author: Rio
 * Date: 2017/06/10
 */

#include <stdexcept>
#include <map>
#include <string>

#include "SDL2/SDL.h"

#include "game.hpp"
#include "graphic.hpp"
#include "robot.hpp"
#include "main.hpp"

using runbot::Game;

Game::Game() try : graphic(), robot(graphic.getRenderer()) {
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

        if(keys["up"]) {
            robot.jump(25);
        } else {
            robot.releaseJump();
        }

        if(keys["right"]) {
            robot.shoot();
        }

        robot.doTick();
        
        int frameTicks = SDL_GetTicks() - frameStart;
        if(frameTicks > runbot::TPF) continue;
        SDL_Delay(runbot::TPF - frameTicks);

        // Render
        draw();
    }
}

void Game::processEvents() {

    SDL_Event eve;
    while(SDL_PollEvent(&eve)) {
        switch(eve.type) {
            case SDL_KEYDOWN:
                switch(eve.key.keysym.sym) {
                    case SDLK_UP:
                        keys["up"] = true;
                        break;
                    case SDLK_RIGHT:
                        keys["right"] = true;
                        break;
                }
                break;
            case SDL_KEYUP:
                switch(eve.key.keysym.sym) {
                    case SDLK_UP:
                        keys["up"] = false;
                        break;
                    case SDLK_RIGHT:
                        keys["right"] = false;
                        break;
                }
                break;
            case SDL_QUIT:
                running = false;
                break;
        }
    }
}

void Game::draw() {

    SDL_Renderer *rend = graphic.getRenderer();
    SDL_Texture *texture = graphic.getGameTexture();
    robot.draw(rend, texture);

    // Apply drawings to window
    graphic.drawToWindow();
}
