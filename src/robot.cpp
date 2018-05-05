/*
 * Author: Rio
 * Date: 2017/05/21
 */

#include <stdexcept>

#include "SDL2/SDL.h"

#include "robot.hpp"
#include "object.hpp"
#include "bullet.hpp"
#include "game.hpp"
#include "graphic.hpp"
#include "collision.hpp"
#include "anim.hpp"
#include "explosion.hpp"

using runbot::Robot;

Robot::Robot(Game *game) :
    Object({0, 0}, {.minPos={20, 0}, .maxPos={Robot::W - 20, Robot::H}}),
    game(game),
    bodyAnim(0, 0, 200, 400, 30, 20, true),
    armAnim(0, 400, 200, 400, 30, 20, false) {
}

void Robot::draw() {

    if(dead) return;

    Graphic &graphic = Graphic::instance();
    SDL_Rect src, des;

    // Body animation
    src = bodyAnim.getCurrentClip();
    des = {pos.x - game->distance, pos.y - game->cameraY, Robot::W, Robot::H};
    graphic.renderImage("robot.png", &src, &des);

    // Arm animation
    src = armAnim.getCurrentClip();
    des = {pos.x - game->distance, pos.y - game->cameraY, Robot::W, Robot::H};
    graphic.renderImage("robot.png", &src, &des);
}

void Robot::doTick(int tick) {

    if(dead) return;

    if(pos.x < game->distance + Robot::W)
        speed.x = game->speed * 2;
    else
        speed.x = game->speed;

    speed.y += 1;

    pos += speed;

    if(pos.x + Robot::W * 2 < game->distance || pos.y > Game::H)
    // Out of map
        die();

    hitbox.speed = speed;
    hitbox.minPos = pos + Vector<int>{20, 0};
    hitbox.maxPos = pos + Vector<int>{Robot::W - 20, Robot::H};

    if(shootCD > 0)
        shootCD--;

    if(!onGround)
        bodyAnim.pause();

    bodyAnim.doTick();
    armAnim.doTick();

    onGround = false;
}

bool Robot::onCollide(Object &other, Direction dir) {
    switch(other.getType()) {
        case TILE:
            if(dir == DOWN) {
                bodyAnim.start();
                onGround = true;
            }
            break;
        case MISSILE:
            die();
            break;
        default:
            break;
    }
    return true;
}

bool Robot::isDead() {
    return false;
}

runbot::Object::Type Robot::getType() {
    return ROBOT;
}

void Robot::reset() {
    pos = {0, 0};
    speed = {0, 0};
    dead = false;
}

void Robot::jump() {
    if(onGround) {
        speed.y = -Robot::JUMP_FORCE;
        onGround = false;
        bodyAnim.pause();
    }
}

void Robot::releaseJump() {
    if(!onGround)
        speed.y += 2;
}

void Robot::shoot() {
    if(shootCD == 0) {
        game->spawn(new Bullet(game, pos + Vector<int>{Robot::W, 102},
                    game->speed, false));
        armAnim.start();
        shootCD = armAnim.getLength();
    }
}

void Robot::die() {
    if(!dead) {
        game->spawn(new Explosion(game, pos, {Robot::W, Robot::H}));
        game->setState(Game::DEAD);
        dead = true;
    }
}
