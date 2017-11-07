/*
 * Author: Rio
 * Date: 2017/11/07
 */

#include <algorithm>
#include <limits>

#include "collision.hpp"
#include "vector.hpp"
#include "object.hpp"

using runbot::Direction;
using runbot::Collision;

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

    Vector<float> distance, speed, relSpeed, entry;
    speed = a.speed - b.speed;

    if(speed.x > 0) {
        distance.x = b.minPos.x - a.maxPos.x;
    } else {
        distance.x = b.maxPos.x - a.minPos.x;
    }

    if(speed.y > 0) {
        distance.y = b.minPos.y - a.maxPos.y;
    } else {
        distance.y = b.maxPos.y - a.minPos.y;
    }

    if(speed.x == 0) {
        entry.x = -std::numeric_limits<float>::infinity();
    } else {
        entry.x = distance.x / speed.x;
    }

    if(speed.y == 0) {
        entry.y = -std::numeric_limits<float>::infinity();
    } else {
        entry.y = distance.y / speed.y;
    }

    float entryTime = std::max(entry.x, entry.y);

    if(entryTime < -1 || entryTime > 0) {
        dir = NONE;
        time = 1;
    } else {
        if(entry.x > entry.y) {
            dir = distance.x < 0 ? LEFT : RIGHT;
        } else {
            dir = distance.y < 0 ? UP : DOWN;
        }
        time = entryTime;
    }
}

Direction Collision::getDirection() {
    /*
    if(overlap.x * overlap.y == 0)
        return NONE;

    if(overlap.y > 0 && overlap.y < Collision::STEP_HEIGHT) // Stepping on small rise
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
    }*/
    return dir;
}

void Collision::solve(Object &a, Object &b) {

    if(time >= -1 && time <= 0) {

        Vector<int> posA = a.getPos();
        Vector<int> posB = b.getPos();

        Vector<float> speedA = a.getSpeed();
        Vector<float> speedB = b.getSpeed();

        posA += speedA * time;
        posB += speedB * time;

        a.setPos(posA);
        b.setPos(posB);

        //a.setSpeed({0, 0});
        //b.setSpeed({0, 0});
    }
}
