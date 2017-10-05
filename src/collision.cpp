/*
 * Author: Rio
 * Date: 2017/10/05
 */

#include "collision.hpp"
#include "vector.hpp"

using runbot::Hitbox;
using runbot::Collision;

Collision::Collision(Hitbox a, Hitbox b) : a(a), b(b) {
    collide = a.collide(b);
}

bool Collision::isColliding() {
    return collide;
}

void Collision::solve() {
    if(!collide) return;

    Vector dir = (a.pos + a.size / 2) - (b.pos + b.size / 2);
}

bool Hitbox::collide(const Hitbox &b) {
    return
        pos.x <= b.pos.x + b.size.x &&
        pos.x + size.x >= b.pos.x &&
        pos.y <= b.pos.y + b.size.y &&
        pos.y + size.y >= b.pos.y;
}
