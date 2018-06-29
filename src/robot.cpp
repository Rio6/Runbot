/*
 * Author: Rio
 * Date: 2017/05/21
 */

#include <stdexcept>

#include "SDL.h"

#include "robot.hpp"
#include "object.hpp"
#include "bullet.hpp"
#include "game.hpp"
#include "graphic.hpp"
#include "collision.hpp"
#include "anim.hpp"
#include "explosion.hpp"

using runbot::Robot;

const float Robot::JUMP_FORCE = 22;
const float Robot::GRAV = 0.8;

Robot::Robot(Game *game) :
    Object({0, Game::H / 4}, {.minPos={20, 0}, .maxPos={Robot::W - 20, Robot::H}}),
    game(game),
    bodyAnim(0, 0, 200, 400, 30, 20, true),
    armAnim(0, 400, 200, 400, 30, 20, false) {
}

void Robot::draw() {

    if(dead) return;

    Graphic &graphic = Graphic::instance();
    SDL_Rect src, des = {pos.x - game->distance, pos.y - game->cameraY, Robot::W, Robot::H};

    // Body animation
    src = bodyAnim.getCurrentClip();
    graphic.renderImage("robot.png", &src, &des);

    // Arm animation
    src = armAnim.getCurrentClip();
    graphic.renderImage("robot.png", &src, &des);
}

void Robot::doTick(int tick) {

    if(dead) return;

    if(speed.x < -game->speed) speed.x = -game->speed;
    if(pos.x < game->distance + Game::W / 5 && speed.x < game->speed * 2)
        speed.x += (game->speed * 2 - speed.x) / 8;
    else if(speed.x > game->speed)
        speed.x += (game->speed - speed.x) / 8;

    speed.y += GRAV;

    pos += speed;

    if(pos.x + Robot::W < game->distance || pos.y > Game::H || hp <= 0)
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
            hp--;
            break;
        case BULLET:
            if(dynamic_cast<Bullet&>(other).isEnemy())
                hp--;
            else
                return false;
            break;
        default:
            break;
    }
    return true;
}

bool Robot::isDead() {
    return dead;
}

runbot::Object::Type Robot::getType() {
    return ROBOT;
}

int Robot::getHP() {
    return hp;
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
        speed.y += GRAV * 2;
}

void Robot::shoot() {
    if(shootCD == 0) {
        game->spawn(new Bullet(game, pos + Vector<int>{Robot::W - 25, 102},
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
