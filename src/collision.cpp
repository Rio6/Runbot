/*
 * This game uses swept AABB collision detection
 *
 * Author: Rio
 * Date: 2017/10/03
 */

#include <algorithm>
#include <cmath>

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
    } else if(speed.x > 0) {
        entryDist.x = hb.minPos.x - ha.maxPos.x;
        exitDist.x = hb.maxPos.x - ha.minPos.x;
    } else {
        if(ha.minPos.x < hb.maxPos.x && hb.minPos.x < ha.maxPos.x) {
            entryDist.x = -1;
            exitDist.x = 1;
        } else {
            entryDist.x = 1;
            exitDist.x = -1;
        }
    }

    if(speed.y < 0) {
        entryDist.y = hb.maxPos.y - ha.minPos.y;
        exitDist.y = hb.minPos.y - ha.maxPos.y;
    } else if(speed.y > 0) {
        entryDist.y = hb.minPos.y - ha.maxPos.y;
        exitDist.y = hb.maxPos.y - ha.minPos.y;
    } else {
        if(ha.minPos.y < hb.maxPos.y && hb.minPos.y < ha.maxPos.y) {
            entryDist.y = -1;
            exitDist.y = 1;
        } else {
            entryDist.y = 1;
            exitDist.y = -1;
        }
    }

    entry.x = entryDist.x / speed.x;
    exit.x = exitDist.x / speed.x;

    entry.y = entryDist.y / speed.y;
    exit.y = exitDist.y / speed.y;

    float entryTime = std::max(entry.x, entry.y);
    float exitTime = std::min(exit.x, exit.y);

    if(exitTime < 0 || entryTime < -5 || entryTime > 0) {
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

    if(dir != NONE) {

        bool aSolve = a->onCollide(*b, dir);
        bool bSolve = b->onCollide(*a, getOpposite(dir));

        if(aSolve && bSolve) {

            Hitbox ha = a->getHitbox();
            Hitbox hb = b->getHitbox();

            Vector<float> speedA = a->getSpeed();
            Vector<float> speedB = b->getSpeed();
            Vector<float> relSpeed = speedB - speedA;

            Vector<float> fixA, fixB;

            switch(dir) {
                case LEFT:
                case RIGHT:
                    if(dir == LEFT && relSpeed.x < 0 || dir == RIGHT && relSpeed.x > 0) break;

                    fixA = {speedA.x * time, 0};
                    fixB = {speedB.x * time, 0};

                    if(std::isinf(ha.mass) || std::isinf(hb.mass)) {
                        speedA = {0, speedA.y};
                        speedB = {0, speedB.y};
                    } else {
                        speedA = {speedB.x + (hb.mass - ha.mass) * relSpeed.x / (ha.mass + hb.mass), speedA.y};
                        speedB = {speedB.x + 2 * ha.mass * relSpeed.x / (ha.mass + hb.mass), speedA.y};
                    }
                    break;
                case UP:
                case DOWN:
                    if(dir == UP && relSpeed.y < 0 || dir == DOWN && relSpeed.y > 0) break;

                    fixA = {0, speedA.y * time};
                    fixB = {0, speedB.y * time};

                    if(std::isinf(ha.mass) || std::isinf(hb.mass)) {
                        speedA = {speedA.x, 0};
                        speedB = {speedB.x, 0};
                    } else {
                        speedA = {speedB.y + 2 * ha.mass * relSpeed.y / (ha.mass + hb.mass), speedA.x};
                        speedB = {speedB.y + (ha.mass - hb.mass) * relSpeed.y / (ha.mass + hb.mass), speedA.x};
                    }
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
