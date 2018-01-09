/*
 * Author: Rio
 * Date: 2018/1/8
 */

#include "object.hpp"
#include "vector.hpp"
#include "collision.hpp"

using runbot::Object;
using runbot::Hitbox;
using runbot::Vector;

Object::Object(Vector<int> pos) : pos(pos) {}
Object::Object(Vector<int> pos, Hitbox hitbox) : pos(pos), hitbox(hitbox) {}
Object::Object(Vector<int> pos, Vector<float> speed,  Hitbox hitbox) : pos(pos), speed(speed), hitbox(hitbox) {}

void Object::doTick(int tick) {}

Vector<int> Object::getPos() {
    return pos;
}

void Object::onCollide(Object &other, Direction dir) {
}

Vector<float> Object::getSpeed() {
    return speed;
}

void Object::setPos(Vector<int> pos) {
    this->pos = pos;
}

void Object::setSpeed(Vector<float> speed) {
    this->speed = speed;
}

Hitbox &Object::getHitbox() {
    return hitbox;
}

bool Object::isOut(int distance) {
    return pos.x - distance < 0;
}
