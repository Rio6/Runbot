/*
 * Author: Rio
 * Date: 2017/10/09
 */

#include <cmath>

#include "collision.hpp"
#include "vector.hpp"
#include "object.hpp"

using runbot::Hitbox;
using runbot::Collision;

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

runbot::Direction Collision::getDirection() {
    if(overlap.x * overlap.y == 0)
        return NONE;
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
    switch(dir) {
        case RIGHT:
        case LEFT:
            a.setPos(a.getPos() - Vector{overlap.x, 0});
            break;
        case UP:
        case DOWN:
            a.setPos(a.getPos() - Vector{0, overlap.y});
            break;
        case NONE:
            return;
    }
    a.setSpeed({0, 0});
}
