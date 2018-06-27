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
#include <cmath>

#include "SDL.h"
#include "SDL_mixer.h"

#include "game.hpp"
#include "graphic.hpp"
#include "robot.hpp"
#include "tile.hpp"
#include "background.hpp"
#include "collision.hpp"
#include "level.hpp"
#include "media.hpp"

#define TOTAL_SCORE (distance / 10 + score)

using runbot::Game;

Game::Game() : level(this) {
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
            reset();
            menu = std::make_unique<StartMenu>(this, highScore.getScore());

            if(bgCh >= 0)
                Mix_HaltChannel(bgCh);
            bgCh = Mix_PlayChannel(-1, Media::get<Mix_Chunk*>("start.wav"), -1);
            break;
        case RUNNING:
            if(SDL_GetNumTouchDevices() > 0)
                menu = std::make_unique<GameMenu>(this);
            else
                menu = nullptr;
            if(state == DEAD)
                reset();

            if(bgCh >= 0)
                Mix_HaltChannel(bgCh);
            bgCh = Mix_FadeInChannel(-1, Media::get<Mix_Chunk*>("bg.wav"), -1, 2000);
            break;
        case PAUSED:
            highScore.updateScore(TOTAL_SCORE);
            menu = std::make_unique<PauseMenu>(this);
            break;
        case DEAD:
            highScore.updateScore(TOTAL_SCORE);
            menu = std::make_unique<DeadMenu>(this, TOTAL_SCORE, highScore.getScore());
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
            case SDL_FINGERUP:
            case SDL_FINGERDOWN:
            case SDL_FINGERMOTION:
                {
                    bool down = eve.type != SDL_FINGERUP;
                    if(menu != nullptr) {
                        Vector<int> pos = {static_cast<int>(eve.tfinger.x * Game::W),
                            static_cast<int>(eve.tfinger.y * Game::H)};
                        if(!menu->onMouse(pos, down)) {
                            if(eve.tfinger.x < .5f)
                                keys["jump"] = down;
                            else
                                keys["shoot"] = down;
                        }
                    }
                    break;
                }
            case SDL_KEYDOWN:
                switch(eve.key.keysym.sym) {
                    case JUMP_KEY:
                        keys["jump"] = true;
                        break;
                    case SHOOT_KEY:
                        keys["shoot"] = true;
                        break;
                    case SDLK_ESCAPE:
                    case SDLK_AC_BACK:
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
                    case JUMP_KEY:
                        keys["jump"] = false;
                        break;
                    case SHOOT_KEY:
                        keys["shoot"] = false;
                        break;
                }
                break;
            case SDL_MOUSEMOTION:
                cursor.x = eve.motion.x;
                cursor.y = eve.motion.y;

                if(!!menu) {
                    Vector<int> pos = {eve.button.x, eve.button.y};
                    menu->onMouse(pos, !!(eve.motion.state & SDL_BUTTON_LMASK));
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if(!!menu && eve.button.button == SDL_BUTTON_LEFT) {
                    Vector<int> pos = {eve.button.x, eve.button.y};
                    menu->onMouse(pos, false);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(!!menu && eve.button.button == SDL_BUTTON_LEFT) {
                    Vector<int> pos = {eve.button.x, eve.button.y};
                    menu->onMouse(pos, true);
                }
                break;
            case SDL_APP_WILLENTERBACKGROUND:
                if(state == RUNNING)
                    setState(PAUSED);
                break;
            case SDL_APP_TERMINATING:
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
            robot->jump();
        } else {
            robot->releaseJump();
        }

        if(keys["shoot"]) {
            robot->shoot();
        }
    }

    // Generate Level
    level.genLevel(distance + Game::W);

    // Tick everything
    for(size_t i = 0; i < objects.size(); i++) {
        if(objects[i]->isDead())
            objects.erase(objects.begin() + i);
        else if(objects[i]->getPos().x < distance + Game::W)
            // Only tick object that are in-screen (left of right screen edge)
            objects[i]->doTick(tick);
    }

    bg.doTick(speed);

    // Resolve collision
    // Only solve objects that are in-screen

    // Find collisions
    std::vector<Collision> colls;
    for(auto it = objects.begin(); it + 1 < objects.end(); it++) {
        if((*it)->getPos().x >= distance + Game::W) continue;
        for(auto jt = it + 1; jt != objects.end(); jt++) {
            if((*jt)->getPos().x >= distance + Game::W) continue;
            colls.emplace_back(it->get(), jt->get());
        }
    }

    // Sort collisions with time
    std::sort(colls.begin(), colls.end());

    // Solve collisions
    for(Collision coll : colls) {
        coll.solve();
    }

    if(state == RUNNING) { // Only do these when game is running

        // Move camera up if robot is too high
        int robotY = robot->getPos().y;
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

    // Draw background
    bg.draw();

    // Draw objects
    for(std::shared_ptr<Object> object : objects)
        object->draw();

    // Draw menu
    if(!!menu) {
        menu->draw();
    }

    if(state == RUNNING) {
        // Draw score
        char distDisplay[32];
        std::sprintf(distDisplay, "SCORE:%5d", TOTAL_SCORE);
        SDL_Rect des = {Game::W - 200, Game::H - 40, 200, 40};
        graphic.renderText(distDisplay, &des);
        // Draw HP
        des = {10, Game::H - 40, 35, 35};
        int hp = robot->getHP();
        for(int i = 0; i < hp; i++) {
            graphic.renderImage("heart.png", nullptr, &des);
            des.x += des.w;
        }
    } else {
        // Draw cursor
        SDL_Rect des = {cursor.x, cursor.y, CURSOR_SIZE, CURSOR_SIZE};
        graphic.renderImage("cursor.png", nullptr, &des);
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
    tick = 0;
    score = 0;

    // Reset objects
    objects.clear();

    // Reset robot
    robot = std::shared_ptr<Robot>(new Robot(this));

    // Put robot in objects, easier to loop through
    objects.push_back(robot);

    // Generate in-screen level
    level.genLevel(distance);
}

void Game::spawn(Object *obj) {
    if(!!obj)
        objects.emplace_back(obj);
}

void Game::addScore(int score) {
    this->score += score;
}

// Return objects that are within range of a position
std::vector<std::shared_ptr<runbot::Object>> Game::getObjectsIn(Vector<int> pos, int xRange, int yRange) {
    std::vector<std::shared_ptr<Object>> rst;

    for(auto &object : objects) {
        Vector<int> relPos = object->getPos() - pos;
        if(std::abs(relPos.x) <= xRange && std::abs(relPos.y) <= yRange) {
            rst.push_back(object);
        }
    }
    return rst;
}
