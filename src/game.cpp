/*
 * Author: Rio
 * Date: 2017/10/09
 */

#include <stdexcept>
#include <map>
#include <string>

#include "SDL2/SDL.h"

#include "game.hpp"
#include "graphic.hpp"
#include "robot.hpp"
#include "tile.hpp"
#include "collision.hpp"
#include "main.hpp"

using runbot::Game;

Game::Game() try : graphic(), robot(graphic.getRenderer()) {
} catch (std::runtime_error exc) {
    logError("Failed to initilize", exc.what());
}

Game::~Game() {
    Tile::freeSprite();
}


void Game::loop() {

    running = true;
    while(running) {
        int frameStart = SDL_GetTicks();

        // Control robot
        processEvents();

        if(keys["up"]) {
            robot.jump(25);
        } else {
            robot.releaseJump();
        }

        if(keys["right"]) {
            robot.shoot();
        }

        // Add a tile
        if(distance % 100 == 0) {
            tiles.push_back(Tile(graphic.getRenderer(),
                        distance + GAME_W, 476, Tile::TILE_GROUND));
        }

        // Tick everything
        robot.doTick(tick, distance);

        for(size_t i = 0; i < tiles.size(); i++) {
            if(tiles[i].isOut(distance))
                tiles.erase(tiles.begin() + i);
            else
                tiles[i].doTick(tick, distance);
        }

        // Resolve collision
        for(Tile tile : tiles) {
            Collision coll(robot.getHitbox(), tile.getHitbox());
            Direction dir = coll.getDirection();
            if(dir != NONE) {
                robot.onCollide(dir);
                tile.onCollide(dir);
            }
            coll.solve(robot, tile);
        }

        tick++;
        distance += speed;

        //if(tick % 100 == 0) speed++;
        
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
    robot.draw(rend, texture, distance);

        for(Tile tile : tiles)
            tile.draw(rend, texture, distance);

    // Apply drawings to window
    graphic.drawToWindow();
}
