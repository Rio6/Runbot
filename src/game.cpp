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

#include "SDL2/SDL.h"

#include "game.hpp"
#include "graphic.hpp"
#include "robot.hpp"
#include "tile.hpp"
#include "background.hpp"
#include "collision.hpp"
#include "level.hpp"

using runbot::Game;

Game::Game() : robot(this), level(this) {
    setState(START);
}

void Game::loop() {

    // Use reset to init
    reset();

    while(state != STOP) {

        int start = SDL_GetTicks();

        processEvents();

        switch(state) {
            case RUNNING:
            case DEAD:
                doTick();
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

    if(newState == state) return;

    switch(newState) {
        case START:
            menu = std::make_unique<StartMenu>(this);
            break;
        case RUNNING:
            menu.release();
            if(state == START || state == DEAD)
                reset();
            break;
        case PAUSED:
            menu = std::make_unique<PauseMenu>(this);
            break;
        case DEAD:
            menu = std::make_unique<DeadMenu>(this, distance);
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
            case SDL_KEYDOWN:
                switch(eve.key.keysym.sym) {
                    case SDLK_UP:
                        keys["jump"] = true;
                        break;
                    case SDLK_RIGHT:
                        keys["shoot"] = true;
                        break;
                    case SDLK_ESCAPE:
                        switch(state) {
                            case RUNNING:
                                setState(PAUSED);
                                break;
                            case PAUSED:
                                setState(RUNNING);
                                break;
                            case DEAD:
                                setState(START);
                                break;
                            case START:
                                setState(STOP);
                                break;
                            default:
                                break;
                        }
                        break;
                }
                break;
            case SDL_KEYUP:
                switch(eve.key.keysym.sym) {
                    case SDLK_UP:
                        keys["jump"] = false;
                        break;
                    case SDLK_RIGHT:
                        keys["shoot"] = false;
                        break;
                }
                break;
            case SDL_MOUSEMOTION:
                cursor.x = eve.motion.x;
                cursor.y = eve.motion.y;
                break;
            case SDL_MOUSEBUTTONUP:
                if(eve.button.clicks) {
                    Vector<int> pos = {eve.button.x, eve.button.y};
                    if(menu != nullptr) {
                        menu->onClick(pos);
                    }
                }
                break;
            case SDL_QUIT:
                setState(STOP);
                break;
        }
    }
}

void Game::doTick() {

    // Robot actions
    if(state == RUNNING) { // Only do these when game is running
        if(keys["jump"]) {
            robot.jump();
        } else {
            robot.releaseJump();
        }

        if(keys["shoot"]) {
            robot.shoot();
        }
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

    if(state == RUNNING) { // Only do these when game is running

        // Move camera up if robot is too high
        int robotY = robot.getPos().y;
        if(robotY < 0)
            cameraY = robotY / 2;
        else
            cameraY /= 2;

        // Make game go faster
        if(tick % 1000 == 0) speed += 0.5;
    }

    tick++;
    distance += speed;
}

void Game::draw() {

    Graphic &graphic = Graphic::instance();

    graphic.clear();

    bg.draw();

    for(std::shared_ptr<Object> object : objects)
        object->draw();

    if(menu != nullptr) {
        menu->draw();
    }

    if(state == RUNNING) {
        // Draw score
        char distDisplay[32];
        std::sprintf(distDisplay, "Distance:%5d", distance / 10);
        SDL_Rect des = {Game::W - 200, Game::H - 40, 200, 40};
        graphic.renderText(distDisplay, &des, 0);
    } else {
        // Draw cursor
        SDL_Rect src = {0, 0, CURSOR_SIZE, CURSOR_SIZE};
        SDL_Rect des = {cursor.x, cursor.y, CURSOR_SIZE, CURSOR_SIZE};
        graphic.renderImage("cursor.png", &src, &des);
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

    // Reset robot
    robot.reset();

    // Put robot in objects, easier to loop through
    objects.emplace_back(&robot, [](Robot *r) {}); // But don't delete robot

    // Put some tiles at the beginning
    for(int i = 0; i < Game::W - Tile::W; i += Tile::W) {
        objects.emplace_back(new Tile(this,
                    {i, Game::H - Tile::H}, Tile::TILE_GROUND));
    }
}

void Game::spawn(Object *obj) {
    objects.emplace_back(obj);
}
