/*
 * Author: Rio
 * Date: 2017/11/02
 */

#include <algorithm>
#include <limits>

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

    /*
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
    }*/

    float entryX, entryY, exitX, exitY;
    Vector<float> speed;
    speed = (a.minPos - a.oldMinPos) + (b.minPos - b.oldMinPos);

    if(speed.x > 0) {
        entryX = b.minPos.x - a.maxPos.x;
        exitX = b.maxPos.x - a.minPos.x;
    } else {
        entryX = a.minPos.x - b.maxPos.x;
        exitX = a.maxPos.x - b.minPos.x;
    }
    if(speed.y > 0) {
        entryY = b.minPos.y - a.maxPos.y;
        exitY = b.maxPos.y - a.minPos.y;
    } else {
        entryY = a.minPos.y - b.maxPos.y;
        exitY = a.maxPos.y - b.minPos.y;
    }

    if(speed.x == 0) {
        entryX = -std::numeric_limits<int>::infinity();
        exitX = std::numeric_limits<int>::infinity();
    } else {
        entryX /= speed.x;
        exitX /= speed.x;
    }

    if(speed.y == 0) {
        entryY = -std::numeric_limits<int>::infinity();
        exitY = std::numeric_limits<int>::infinity();
    } else {
        entryY /= speed.y;
        exitY /= speed.y;
    }

    float entry = std::max(entryX, entryY);
    float exit = std::min(exitX, exitY);

    if(entry > exit || (entryX < 0 && entryY < 0) || (exitX > 1 && exitY > 1)) {
        dir = NONE;
    } else {
        if(entryX > entryY) {
            dir = entryX < 0 ? LEFT : RIGHT;
        } else {
            dir = entryY < 0 ? UP : DOWN;
        }
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

// a is the object to be moved
void Collision::solve(Object &a, Object &b) {
    Direction dir = getDirection();
    Vector<float> aSpeed = a.getSpeed();
    /*
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
    */
    a.setSpeed(aSpeed);
}
