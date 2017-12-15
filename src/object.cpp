/*
 * Author: Rio
 * Date: 2017/10/27
 */

#include "object.hpp"
#include "vector.hpp"
#include "collision.hpp"

using runbot::Object;

Object::Object(Vector<int> pos) : pos(pos) {}
Object::Object(Vector<int> pos, Hitbox hitbox) : pos(pos), hitbox(hitbox) {}

void Object::doTick(int tick) {}

runbot::Vector<int> Object::getPos() {
    return pos;
}

void Object::onCollide(Object &other, Direction dir) {
}

runbot::Vector<float> Object::getSpeed() {
    return speed;
}

void Object::setPos(Vector<int> pos) {
    this->pos = pos;
}

void Object::setSpeed(Vector<float> speed) {
    this->speed = speed;
}

runbot::Hitbox &Object::getHitbox() {
    return hitbox;
}

bool Object::isOut(int distance) {
    return pos.x - distance < 0;
}
