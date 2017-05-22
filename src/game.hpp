/*
 * Author: Rio
 * Date: 2017/05/21
 */

#ifndef _GAME_H_
#define _GAME_H_

#include "graphic.hpp"
#include "robot.hpp"

namespace runbot {
    class Game {
        public:
            Game();
            ~Game();
            void loop();
            Robot &getRobot();

        private:
            bool running;

            Graphic graphic;
            Robot robot;

            void processEvents();
    };
};

#endif
