/*
 * Author: Rio
 * Date: 2017/05/28
 */

#ifndef _GAME_H_
#define _GAME_H_

#include <map>
#include <string>

#include "graphic.hpp"
#include "robot.hpp"

namespace runbot {
    const int GAME_W = 1024;
    const int GAME_H = 576;
    const char *const NAME = "Runbot";
    const int FPS = 30;
    const int TPF = 1000 / FPS; // ticks per frame

    void logError(const char*, const char*);

    class Game {
        public:
            Game();
            ~Game();
            void loop();

        private:
            bool running;
            std::map<std::string, bool> keys;
            Graphic graphic;
            Robot robot;

            void processEvents();
            void draw();
    };
};

#endif
