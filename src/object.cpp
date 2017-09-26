/*
 * Author: Rio
 * Date: 2017/09/26
 */

#include "object.hpp"
#include "util.hpp"

using runbot::Object;

Object::Object(Vector pos) : pos(pos) {}
void Object::doTick(int tick) {}

runbot::Vector Object::getPos() {
    return pos;
}

runbot::Vector Object::getSpeed() {
    return speed;
}

bool Object::isOut(int distance) {
    return pos.x - distance < 0;
}
