/*
 * This game uses swept AABB collision detection
 *
 * Author: Rio
 * Date: 2017/10/03
 */

#include <algorithm>

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

Collision::Collision(Object *a, Object *b) : a(a), b(b) {
    calculate();
};

void Collision::calculate() {

    Hitbox ha = a->getHitbox();
    Hitbox hb = b->getHitbox();

    Vector<int> entryDist, exitDist;
    Vector<float> speed, entry, exit;
    speed = ha.speed - hb.speed;

    if(speed.x < 0) {
        entryDist.x = hb.maxPos.x - ha.minPos.x;
        exitDist.x = hb.minPos.x - ha.maxPos.x;
    } else {
        entryDist.x = hb.minPos.x - ha.maxPos.x;
        exitDist.x = hb.maxPos.x - ha.minPos.x;
    }

    if(speed.y < 0) {
        entryDist.y = hb.maxPos.y - ha.minPos.y;
        exitDist.y = hb.minPos.y - ha.maxPos.y;
    } else {
        entryDist.y = hb.minPos.y - ha.maxPos.y;
        exitDist.y = hb.maxPos.y - ha.minPos.y;
    }

    entry.x = entryDist.x / speed.x;
    exit.x = exitDist.x / speed.x;

    entry.y = entryDist.y / speed.y;
    exit.y = exitDist.y / speed.y;

    float entryTime = std::max(entry.x, entry.y);
    float exitTime = std::min(exit.x, exit.y);

    if(exitTime <= 0 || entryTime < -1 || entryTime > 0) {
        dir = NONE;
        time = 1;
    } else {
        if(entry.x > entry.y) {
            dir = entryDist.x > 0 ? LEFT : RIGHT;
        } else {
            dir = entryDist.y > 0 ? UP : DOWN;
        }
        time = entryTime;
    }
}

void Collision::solve() {
    // Just move objects back to where they touch
    // Not a super fancy/accurate solving method

    // Recalculate before solving
    calculate();

    if(time >= -1 && time <= 0) {

        bool aSolve = a->onCollide(*b, dir);
        bool bSolve = b->onCollide(*a, getOpposite(dir));

        if(aSolve && bSolve) {

            Vector<float> speedA = a->getSpeed();
            Vector<float> speedB = b->getSpeed();
            Vector<float> fixA, fixB;

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

            Vector<int> posA = a->getPos();
            Vector<int> posB = b->getPos();

            posA += fixA;
            posB += fixB;

            a->setPos(posA);
            b->setPos(posB);

            a->setSpeed(speedA);
            b->setSpeed(speedB);
        }
    }
}

bool Collision::operator<(const Collision &rhs) const {
    return this->time < rhs.time;
}
