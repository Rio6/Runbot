/*
 * Author: Rio
 * Date: 2017/10/03
 */

#include "object.hpp"
#include "vector.hpp"
#include "collision.hpp"

using runbot::Object;

Object::Object(Vector pos) : pos(pos) {}
Object::Object(Vector pos, Hitbox hitbox) : pos(pos), hitbox(hitbox) {}

void Object::doTick(int tick, int distance) {}

runbot::Vector Object::getPos() {
    return pos;
}

runbot::Vector Object::getSpeed() {
    return speed;
}

runbot::Hitbox Object::getHitbox() {
    return hitbox;
}

bool Object::isOut(int distance) {
    return pos.x - distance < 0;
}
