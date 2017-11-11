/*
 * Author: Rio
 * Date: 2017/11/09
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
        entryDist.x = b.maxPos.x - a.minPos.x;
        exitDist.x = b.minPos.x - a.maxPos.x;
    }

    if(speed.y > 0) {
        entryDist.y = b.minPos.y - a.maxPos.y;
        exitDist.y = b.maxPos.y - a.minPos.y;
    } else {
        entryDist.y = b.maxPos.y - a.minPos.y;
        exitDist.y = b.minPos.y - a.maxPos.y;
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
        if(entry.x > entry.y) {
            dir = speed.x < 0 ? LEFT : RIGHT;
        } else {
            dir = speed.y < 0 ? UP : DOWN;
        }
        time = entryTime;
    }
}

Direction Collision::getDirection() {
    return dir;
}

void Collision::solve(Object &a, Object &b) {

    if(time >= -1 && time <= 0) {

        Vector<float> speedA = a.getSpeed();
        Vector<float> speedB = b.getSpeed();
        Vector<float> fixA, fixB;

        SDL_Log("%d", dir);

        switch(dir) {
            case LEFT:
            case RIGHT:
                fixA = {speedA.x * time, 0};
                fixB = {speedB.x * time, 0};
                speedA = {0, speedA.y};
                speedB = {0, speedB.y};
                break;
            case UP:
            case DOWN:
                fixA = {0, speedA.y * time};
                fixB = {0, speedB.y * time};
                speedA = {speedA.x, 0};
                speedB = {speedB.x, 0};
                break;
            default:
                return;
        }

        Vector<int> posA = a.getPos();
        Vector<int> posB = b.getPos();

        posA += fixA;
        posB += fixB;

        a.setPos(posA);
        b.setPos(posB);

        a.setSpeed(speedA);
        b.setSpeed(speedB);
    }
}
