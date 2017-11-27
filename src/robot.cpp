/*
 * Author: Rio
 * Date: 2017/11/07
 */

#include <stdexcept>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "robot.hpp"
#include "game.hpp"
#include "collision.hpp"
#include "anim.hpp"

using runbot::Robot;

Robot::Robot(Game *game, SDL_Renderer *rend) :
    Object({0, 0}, {.minPos={20, 0}, .maxPos={Robot::W - 40, Robot::H}}),
    game(game),
    bodyAnim(0, 0, 200, 400, 30, true),
    armAnim(0, 400, 200, 400, 30, false) {

    SDL_Surface *loadSurface = IMG_Load("assets/robot.png");
    if(loadSurface == NULL)
        throw std::runtime_error(IMG_GetError());

    sprite = SDL_CreateTextureFromSurface(rend, loadSurface);
    if(sprite == NULL) {
        SDL_FreeSurface(loadSurface);
        throw std::runtime_error(SDL_GetError());
    }

    bodyAnim.createClips(loadSurface->w / 200);
    armAnim.createClips(loadSurface->w / 200);

    SDL_FreeSurface(loadSurface);
}

Robot::~Robot() {
    SDL_DestroyTexture(sprite);
}

void Robot::draw(SDL_Renderer *rend) {
    SDL_Rect src, des;

    // Body animation
    src = bodyAnim.getCurrentClip();
    des = {pos.x - game->distance, pos.y, Robot::W, Robot::H};
    SDL_RenderCopy(rend, sprite, &src, &des);

    // Arm animation
    src = armAnim.getCurrentClip();
    des = {pos.x - game->distance, pos.y, Robot::W, Robot::H};
    SDL_RenderCopy(rend, sprite, &src, &des);
}

void Robot::doTick(int tick) {

    if(pos.x < game->distance + Robot::W)
        speed.x = game->speed * 2;
    else
        speed.x = game->speed;

    speed.y += 1;

    pos.x += speed.x;
    pos.y += speed.y;

    hitbox.speed = speed;
    hitbox.minPos = pos + 20;
    hitbox.maxPos = pos + Vector<int>{Robot::W - 40, Robot::H};

    if(shootCD > 0)
        shootCD--;

    if(!onGround)
        bodyAnim.pause();

    bodyAnim.doTick();
    armAnim.doTick();

    onGround = false;
}

void Robot::onCollide(Direction dir) {
    if(dir == DOWN) {
        bodyAnim.start();
        onGround = true;
    }
}

void Robot::setPos(Vector<int> pos) {
    this->pos = pos;
    hitbox.minPos = pos + 20;
    hitbox.maxPos = pos + Vector<int>{Robot::W - 40, Robot::H};
}

void Robot::setSpeed(Vector<float> speed) {
    this->speed = speed;
    hitbox.speed = speed;
}

bool Robot::isOut(int distance) {
    return pos.x + Robot::W * 2 < distance || pos.y > Game::H;
}

void Robot::jump() {
    if(jumpReleased && onGround) {
        speed.y = -Robot::JUMP_FORCE;
        jumpReleased = false;
        onGround = false;
        bodyAnim.pause();
    }
}

void Robot::releaseJump() {
    if(onGround)
        jumpReleased = true;
    else
        speed.y += 2;
}

void Robot::shoot() {
    if(shootCD == 0) {
        armAnim.start();
        shootCD = armAnim.getLength();
    }
}
