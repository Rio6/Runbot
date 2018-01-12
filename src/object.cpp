/*
 * Author: Rio
 * Date: 2018/1/11
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

bool Object::onCollide(Object &other, Direction dir) {
    return true;
}

Vector<float> Object::getSpeed() {
    return speed;
}

void Object::setPos(Vector<int> pos) {
    Vector<int> diff = pos - this->pos;
    this->pos = pos;
    hitbox.minPos += diff;
    hitbox.maxPos += diff;
}

void Object::setSpeed(Vector<float> speed) {
    this->speed = speed;
    hitbox.speed = speed;
}

Hitbox &Object::getHitbox() {
    return hitbox;
}

bool Object::isDead() {
    return false;
}
