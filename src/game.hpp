/*
 * Author: Rio
 * Date: 2017/05/22
 */

#ifndef _GAME_H_
#define _GAME_H_

#include "graphic.hpp"
#include "robot.hpp"

namespace runbot {
    class Game {
        private:
            bool running;
            Graphic graphic;

            void processEvents();

        public:
            Robot robot;

            Game();
            ~Game();
            void loop();
    };
};

#endif
