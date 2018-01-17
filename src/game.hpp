/*
 * Author: Rio
 * Date: 2017/05/21
 */

#ifndef _GAME_H_
#define _GAME_H_

#include <memory>
#include <map>
#include <vector>

#include "graphic.hpp"
#include "robot.hpp"
#include "object.hpp"
#include "background.hpp"
#include "level.hpp"

namespace runbot {
    const char *const NAME = "Runbot";
    const int FPS = 60;
    const int MPF = 1000 / FPS; // ms per frame

    class Game {
        public:
            static const int W = 1024;
            static const int H = 576;

            int distance = 0;
            int tick = 0;
            float speed = 5;

            Game();
            void loop();
            void spawn(Object*);

        private:
            const int CURSOR_SIZE = 20;
            Vector<int> cursor {0, -CURSOR_SIZE};

            std::map<SDL_Keycode, bool> keys;

            Robot robot;
            std::vector<std::shared_ptr<Object>> objects;
            Level level;
            Background bg;

            bool running = false;

            void processEvents();
            void draw();
    };
};

#endif
