/*
 * Author: Rio
 * Date: 2017/10/27
 */

#include <cmath>

#include "collision.hpp"
#include "vector.hpp"
#include "object.hpp"

using runbot::Hitbox;
using runbot::Direction;
using runbot::Collision;

void Hitbox::updateOldPos() {
    oldMinPos = minPos;
    oldMaxPos = maxPos;
}

Direction runbot::getOpposite(Direction d) {
    switch(d) {
        case LEFT:
            return RIGHT;
        case RIGHT:
            return LEFT;
        case UP:
            return DOWN;
        case DOWN:
            return UP;
        default:
            return NONE;
    }
}

Collision::Collision(const Hitbox &a, const Hitbox &b) {

    // Calculate overlaps
    if(a.minPos.x < b.maxPos.x && a.maxPos.x > b.minPos.x) {
        if((a.minPos.x + a.maxPos.x) / 2 < (b.minPos.x + b.maxPos.x) / 2)
            overlap.x = a.maxPos.x - b.minPos.x;
        else
            overlap.x = a.minPos.x - b.maxPos.x;
    }
    if(a.minPos.y < b.maxPos.y && a.maxPos.y > b.minPos.y) {
        if((a.minPos.y + a.maxPos.y) / 2 < (b.minPos.y + b.maxPos.y) / 2)
            overlap.y = a.maxPos.y - b.minPos.y;
        else
            overlap.y = a.minPos.y - b.maxPos.y;
    }
}

Direction Collision::getDirection() {
    if(overlap.x * overlap.y == 0)
        return NONE;

    if(overlap.y > 0 && overlap.y < 20) // Stepping on small rise
        return DOWN;

    if(std::abs(overlap.x) < std::abs(overlap.y)) {
        if(overlap.x > 0)
            return RIGHT;
        else
            return LEFT;
    } else {
        if(overlap.y > 0)
            return DOWN;
        else
            return UP;
    }
}

// a is the object to be moved
void Collision::solve(Object &a, Object &b) {
    Direction dir = getDirection();
    Vector aSpeed = a.getSpeed();
    Vector relSpeed = aSpeed - b.getSpeed();
    switch(dir) {
        case RIGHT:
            if(relSpeed.x > 0) {
                a.setPos(a.getPos() - Vector{overlap.x, 0});
                aSpeed.x = 0;
            }
            break;
        case LEFT:
            if(relSpeed.x < 0) {
                a.setPos(a.getPos() - Vector{overlap.x, 0});
                aSpeed.x = 0;
            }
            break;
        case UP:
            if(relSpeed.y < 0) {
                a.setPos(a.getPos() - Vector{0, overlap.y});
                aSpeed.y = 0;
            }
            break;
        case DOWN:
            if(relSpeed.y > 0) {
                a.setPos(a.getPos() - Vector{0, overlap.y});
                aSpeed.y = 0;
            }
            break;
        case NONE:
            return;
    }
    a.setSpeed(aSpeed);
}
