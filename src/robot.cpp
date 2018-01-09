/*
 * Author: Rio
 * Date: 2018/1/8
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

using runbot::Robot;

Robot::Robot(Game *game) :
    Object({0, 0}, {.minPos={20, 0}, .maxPos={Robot::W - 40, Robot::H}}),
    game(game),
    bodyAnim(0, 0, 200, 400, 30, true),
    armAnim(0, 400, 200, 400, 30, false) {

    bodyAnim.createClips(20);
    armAnim.createClips(20);
}

Robot::~Robot() {
}

void Robot::draw() {
    Graphic &graphic = Graphic::instance();
    SDL_Rect src, des;

    // Body animation
    src = bodyAnim.getCurrentClip();
    des = {pos.x - game->distance, pos.y, Robot::W, Robot::H};
    graphic.renderImage(ROBOT_IMG, &src, &des);

    // Arm animation
    src = armAnim.getCurrentClip();
    des = {pos.x - game->distance, pos.y, Robot::W, Robot::H};
    graphic.renderImage(ROBOT_IMG, &src, &des);
}

void Robot::doTick(int tick) {

    if(pos.x < game->distance + Robot::W)
        speed.x = game->speed * 2;
    else
        speed.x = game->speed;

    speed.y += 1;

    pos += speed;

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

void Robot::onCollide(Object &other, Direction dir) {
    if(other.getType() == TILE && dir == DOWN) {
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

runbot::Object::Type Robot::getType() {
    return ROBOT;
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
        game->spawn(new Bullet(game, pos +
                    Vector<int>{Robot::W / 2, 102}));
        armAnim.start();
        shootCD = armAnim.getLength();
    }
}
