/*
 * Author: Rio
 * Date: 2017/10/23
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
    const char *const NAME = "Runbot";
    const int FPS = 60;
    const int TPF = 1000 / FPS; // ticks per frame

    class Game {
        public:
            static const int W = 1024;
            static const int H = 576;

            int distance = 0;
            int tick = 0;
            float speed = 5;

            Game();
            ~Game();
            void loop();

        private:
            std::map<std::string, bool> keys;
            Graphic graphic;
            Robot robot;
            std::vector<Tile> tiles;
            bool running = false;

            void processEvents();
            void draw();
    };
};

#endif
