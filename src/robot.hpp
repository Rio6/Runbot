/*
 * Author: Rio
 * Date: 2017/05/21
 */

#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "graphic.hpp"
#include "anim.hpp"

namespace runbot {
    class Robot {
        private:
            int y;
            int frame;
            Animation anim;

        public:
            static const int w = 200;
            static const int h = 400;
            Robot(Graphic &graphic);
            ~Robot();
            Animation &getAnimaion();
    };
};

#endif
