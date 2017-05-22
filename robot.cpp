/*
 * Author: Rio
 * Date: 2017/05/21
 */

#include "robot.hpp"
#include "graphic.hpp"
#include "anim.hpp"

using runbot::Robot;

Robot::Robot(Graphic &graphic) :
    anim(graphic, "assets/robot.png", 0, 0, Robot::w, Robot::h) {
}

Robot::~Robot() {};

runbot::Animation &Robot::getAnimaion() {
    return anim;
}
