/*
 * Author: Rio
 * Date: 2017/10/03
 */

#include "util.hpp"

using runbot::Vector;
using runbot::Hitbox;

bool Hitbox::collide(const Hitbox &b) {
    return
        pos.x <= b.pos.x + b.size.x &&
        pos.x + size.x >= b.pos.x &&
        pos.y <= b.pos.y + b.size.y &&
        pos.y + size.y >= b.pos.y;
}
