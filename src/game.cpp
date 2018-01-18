/*
 * Author: Rio
 * Date: 2017/05/21
 */

#include <memory>
#include <stdexcept>
#include <algorithm>
#include <map>

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
}

void Game::loop() {

    // Put robot in objects
    objects.emplace_back(&robot, [](Robot *r) {}); // Don't delete robot

    // Some tiles at the beginning
    for(int i = 0; i < Game::W - Tile::W; i += Tile::W) {
        objects.emplace_back(new Tile(this,
                    {i, Game::H - Tile::H}, Tile::TILE_GROUND));
    }

    running = true;
    while(running) {

        int start = SDL_GetTicks();

        // Control robot
        processEvents();

        if(keys[SDLK_UP]) {
            robot.jump();
        } else {
            robot.releaseJump();
        }

        if(keys[SDLK_RIGHT]) {
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

        bg.doTick();

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
            cameraY = robotY;
        else
            cameraY = 0;

        tick++;
        distance += speed;

        if(tick % 1000 == 0) speed++;

        int ticked = SDL_GetTicks() - start;
        if(SDL_TICKS_PASSED(ticked, runbot::MPF)) continue;
        SDL_Delay(runbot::MPF - ticked);

        // Render
        draw();
    }

    // Reset
    objects.clear();
}

void Game::processEvents() {

    SDL_Event eve;
    while(SDL_PollEvent(&eve)) {
        switch(eve.type) {
            case SDL_KEYDOWN:
                switch(eve.key.keysym.sym) {
                    case SDLK_UP:
                        keys[SDLK_UP] = true;
                        break;
                    case SDLK_RIGHT:
                        keys[SDLK_RIGHT] = true;
                        break;
                }
                break;
            case SDL_KEYUP:
                switch(eve.key.keysym.sym) {
                    case SDLK_UP:
                        keys[SDLK_UP] = false;
                        break;
                    case SDLK_RIGHT:
                        keys[SDLK_RIGHT] = false;
                        break;
                    case SDLK_AC_BACK:
                        running = false;
                        break;
                }
                break;
            case SDL_MOUSEMOTION:
                cursor.x = eve.motion.x;
                cursor.y = eve.motion.y;
                break;
            case SDL_QUIT:
                running = false;
                break;
        }
    }
}

void Game::draw() {

    Graphic &graphic = Graphic::instance();

    graphic.clear();

    bg.draw();

    for(std::shared_ptr<Object> object : objects)
        object->draw();

    SDL_Rect src = {0, 0, CURSOR_SIZE, CURSOR_SIZE};
    SDL_Rect des = {cursor.x, cursor.y, CURSOR_SIZE, CURSOR_SIZE};
    graphic.renderImage(CURSOR_IMG, &src, &des);

    // Apply drawings to window
    graphic.update();
}

void Game::spawn(Object *obj) {
    objects.emplace_back(obj);
}
