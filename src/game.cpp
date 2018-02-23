/*
 * Author: Rio
 * Date: 2017/05/21
 */

#include <memory>
#include <stdexcept>
#include <algorithm>
#include <map>
#include <string>
#include <cstdio>

#include "SDL.h"

#include "game.hpp"
#include "graphic.hpp"
#include "robot.hpp"
#include "tile.hpp"
#include "background.hpp"
#include "collision.hpp"
#include "level.hpp"

using runbot::Game;

Game::Game() : robot(this), level(this), startMenu(this), pauseMenu(this) {
}

void Game::loop() {

    // Use reset to init
    reset();

    while(state != STOP) {

        int start = SDL_GetTicks();

        processEvents();

        switch(state) {
            case MENU:
                break;
            case RUNNING:
                doTick();
                break;
            case PAUSED:
                break;
            default:
                break;
        }

        int ticked = SDL_GetTicks() - start;
        if(SDL_TICKS_PASSED(ticked, runbot::MPF)) continue;
        SDL_Delay(runbot::MPF - ticked);

        // Render
        draw();
    }
}

void Game::setState(State newState) {
    switch(newState) {
        case RUNNING:
            if(state == MENU)
                reset();
            break;
        default:
            break;
    }

    state = newState;
}

void Game::processEvents() {

    SDL_Event eve;
    while(SDL_PollEvent(&eve)) {
        switch(eve.type) {
            case SDL_FINGERDOWN:
                if(eve.tfinger.x < .5f) {
                        keys["jump"] = true;
                } else {
                    keys["shoot"] = true;
                }
                break;
            case SDL_FINGERUP:
                if(state == MENU) {
                    Vector<int> pos {(int) (eve.tfinger.x * Game::W), (int) (eve.tfinger.y * Game::H)};
                    startMenu.onClick(pos);
                }
                if(eve.tfinger.x < .5f) {
                        keys["jump"] = false;
                } else {
                    keys["shoot"] = false;
                }
                break;
            case SDL_KEYUP:
                switch(eve.key.keysym.sym) {
                    case SDLK_AC_BACK:
                        if(state == RUNNING)
                            setState(PAUSED);
                        else if(state == PAUSED)
                            setState(RUNNING);
                        break;
                }
                break;
            case SDL_QUIT:
                state = STOP;
                break;
        }
    }
}

void Game::doTick() {

    if(keys["jump"]) {
        robot.jump();
    } else {
        robot.releaseJump();
    }

    if(keys["shoot"]) {
        robot.shoot();
    }

    // Generate Level
    level.genLevel(distance + Game::W);

    // Tick everything
    for(size_t i = 0; i < objects.size(); i++) {
        if(objects[i]->isDead())
            objects.erase(objects.begin() + i);
        else
            objects[i]->doTick(tick);
    }

    bg.doTick(speed);

    // Resolve collision
    std::vector<Collision> colls;
    for(auto it = objects.begin(); it + 1 != objects.end(); it++) {
        for(auto jt = it + 1; jt != objects.end(); jt++) {
            colls.emplace_back((*it).get(), (*jt).get());
        }
    }

    // Sort collision with time
    std::sort(colls.begin(), colls.end());

    for(Collision coll : colls) {
        coll.solve();
    }

    int robotY = robot.getPos().y;
    if(robotY < 0)
        cameraY = robotY / 2;
    else
        cameraY /= 2;

    tick++;
    distance += speed;

    if(tick % 1000 == 0) speed += 0.5;
}

void Game::draw() {

    Graphic &graphic = Graphic::instance();

    graphic.clear();

    bg.draw();

    for(std::shared_ptr<Object> object : objects)
        object->draw();

    if(state == MENU) {
        startMenu.draw();
    } else if(state == PAUSED) {
        pauseMenu.draw();
    }

    if(state == RUNNING) {
        char distDisplay[32];
        std::sprintf(distDisplay, "Distance:%5d", distance / 10);
        SDL_Rect des = {Game::W - 200, Game::H - 40, 200, 40};
        graphic.renderText(distDisplay, &des);
    } else {
        SDL_Rect src = {0, 0, CURSOR_SIZE, CURSOR_SIZE};
        SDL_Rect des = {cursor.x, cursor.y, CURSOR_SIZE, CURSOR_SIZE};
        graphic.renderImage(CURSOR_IMG, &src, &des);
    }

    // Apply drawings to window
    graphic.update();
}

void Game::reset() {

    // Reset level generator
    level.reset();

    // Reset numbers
    distance = 0;
    speed = 5;

    // Reset objects
    objects.clear();

    // Put robot in objects
    objects.emplace_back(&robot, [](Robot *r) {}); // Don't delete robot

    // Put some tiles at the beginning
    for(int i = 0; i < Game::W - Tile::W; i += Tile::W) {
        objects.emplace_back(new Tile(this,
                    {i, Game::H - Tile::H}, Tile::TILE_GROUND));
    }
}

void Game::spawn(Object *obj) {
    objects.emplace_back(obj);
}
