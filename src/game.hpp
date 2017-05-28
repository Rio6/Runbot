/*
 * Author: Rio
 * Date: 2017/05/22
 */

#ifndef _GAME_H_
#define _GAME_H_

#include "graphic.hpp"
#include "robot.hpp"

namespace runbot {
    const int GAME_W = 640;
    const int GAME_H = 480;
    const char *const NAME = "Runbot";
    const int FPS = 30;
    const int TPF = 1000 / FPS; // ticks per frame

    void logError(const char*, const char*);

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
