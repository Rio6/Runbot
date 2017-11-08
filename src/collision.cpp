/*
 * Author: Rio
 * Date: 2017/11/08
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

    Vector<float> entryDist, exitDist, speed, relSpeed, entry, exit;
    speed = a.speed - b.speed;

    if(speed.x > 0) {
        entryDist.x = b.minPos.x - a.maxPos.x;
        exitDist.x = b.maxPos.x - a.minPos.x;
    } else {
        entryDist.x = a.minPos.x - b.maxPos.x;
        exitDist.x = a.maxPos.x - b.minPos.x;
    }

    if(speed.y > 0) {
        entryDist.y = b.minPos.y - a.maxPos.y;
        exitDist.y = b.maxPos.y - a.minPos.y;
    } else {
        entryDist.y = a.minPos.y - b.maxPos.y;
        exitDist.y = a.maxPos.y - b.minPos.y;
    }

    if(speed.x == 0) {
        entry.x = -std::numeric_limits<float>::infinity();
        exit.x = -std::numeric_limits<float>::infinity();
    } else {
        entry.x = entryDist.x / speed.x;
        exit.x = exitDist.x / speed.x;
    }

    if(speed.y == 0) {
        entry.y = -std::numeric_limits<float>::infinity();
        exit.y = -std::numeric_limits<float>::infinity();
    } else {
        entry.y = entryDist.y / speed.y;
        exit.y = exitDist.y / speed.y;
    }

    float entryTime = std::max(entry.x, entry.y);
    float exitTime = std::min(exit.x, exit.y);

    if(exitTime <= 0 || entryTime < -1 || entryTime > 0) {
        dir = NONE;
        time = 1;
    } else {
        SDL_Log("entry %d: x: %f\ty: %f\ttime: %f", SDL_GetTicks(), entry.x, entry.y, entryTime);
        SDL_Log("exit  %d: x: %f\ty: %f\ttime: %f", SDL_GetTicks(), exit.x, exit.y, exitTime);
        if(entry.x > entry.y) {
            dir = speed.x < 0 ? LEFT : RIGHT;
        } else {
            dir = speed.y < 0 ? UP : DOWN;
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
