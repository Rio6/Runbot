/*
 * Author: Rio
 * Date: 2017/09/21
 */

#ifndef _GAME_H_
#define _GAME_H_

#include <map>
#include <string>
#include <vector>

#include "graphic.hpp"
#include "robot.hpp"
#include "tile.hpp"

namespace runbot {
    const int GAME_W = 1024;
    const int GAME_H = 576;
    const char *const NAME = "Runbot";
    const int FPS = 60;
    const int TPF = 1000 / FPS; // ticks per frame

    class Game {
        public:
            Game();
            ~Game();
            void loop();

        private:
            std::map<std::string, bool> keys;
            Graphic graphic;
            Robot robot;
            std::vector<Tile> tiles;
            bool running = false;
            int distance = 0; // aka robot's x
            int tick = 0;
            int speed = 5;

            void processEvents();
            void draw();
    };
};

#endif
