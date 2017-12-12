/*
 * Author: Rio
 * Date: 2017/11/29
 */

#include <stdexcept>
#include <map>
#include <string>

#include "SDL2/SDL.h"

#include "game.hpp"
#include "graphic.hpp"
#include "robot.hpp"
#include "tile.hpp"
#include "background.hpp"
#include "collision.hpp"

using runbot::Game;

Game::Game() : robot(this) {
    try {
        Graphic::instance(); // Create an instance of singleton
    } catch(std::runtime_error e) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Failed to initilize: %s", e.what());
    }
}

Game::~Game() {
}

void Game::loop() {

    for(int i = 0; i < Game::W - Tile::W; i += Tile::W) {
        tiles.push_back(Tile(this, i, Game::H, Tile::TILE_GROUND));
    }

    running = true;
    while(running) {

#ifndef USE_VSYNC
        int frameStart = SDL_GetTicks();
#endif

        // Control robot
        processEvents();

        if(keys["up"]) {
            robot.jump();
        } else {
            robot.releaseJump();
        }

        if(keys["right"]) {
            robot.shoot();
        }

        if(keys["down"]) {
            robot.setSpeed({speed, 100});
        }

        // Add a tile
        if(distance % Tile::W == 0) {
            tiles.push_back(Tile(this, distance + Game::W, Game::H, Tile::TILE_GROUND));
            tiles.push_back(Tile(this, distance + Game::W, Game::H - tick / 2 % Game::H, Tile::TILE_GROUND));
            tiles.push_back(Tile(this, distance + Game::W, Game::H - std::rand() % Game::H, Tile::TILE_GROUND));
        }

        // Tick everything
        robot.doTick(tick);

        for(size_t i = 0; i < tiles.size(); i++) {
            if(tiles[i].isOut(distance))
                tiles.erase(tiles.begin() + i);
            else
                tiles[i].doTick(tick);
        }

        // Resolve collision
        for(Tile tile : tiles) {
            Collision coll(robot.getHitbox(), tile.getHitbox());
            Direction dir = coll.getDirection();
            if(dir != NONE) {
                robot.onCollide(dir);
                tile.onCollide(getOpposite(dir));
            }
            coll.solve(robot, tile);
        }

        if(robot.isOut(distance)) {
            robot.setSpeed({speed, 0});
            robot.setPos({distance, 0});
        }

        bg.doTick();

        tick++;
        distance += speed;

        //if(tick % 100 == 0) speed++;

#ifndef USE_VSYNC
        int frameTicks = SDL_GetTicks() - frameStart;
        if(frameTicks > runbot::TPF) continue;
        SDL_Delay(runbot::TPF - frameTicks);
#endif

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
                    case SDLK_DOWN:
                        keys["down"] = true;
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
                    case SDLK_DOWN:
                        keys["down"] = false;
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

    Graphic &graphic = Graphic::instance();

    graphic.clear();

    bg.draw();

    for(Tile tile : tiles)
        tile.draw();

    robot.draw();

    // Apply drawings to window
    graphic.update();
}
