/*
 * Author: Rio
 * Date: 2017/05/21
 */

#ifndef _GAME_H_
#define _GAME_H_

#include <memory>
#include <map>
#include <vector>
#include <string>

#include "graphic.hpp"
#include "robot.hpp"
#include "object.hpp"
#include "background.hpp"
#include "level.hpp"
#include "menu.hpp"
#include "highscore.hpp"

namespace runbot {
    const char *const NAME = "Runbot";
    const int FPS = 60;
    const int MPF = 1000 / FPS; // ms per frame

    class Game {

        public:
            enum State {
                START,
                RUNNING,
                PAUSED,
                DEAD,
                STOP
            };

            static const int W = 1024;
            static const int H = 576;

            int cameraY = 0;
            int distance = 0;
            float speed = 5;

            Game();
            void loop();
            void setState(State);
            void spawn(Object*);
            void addScore(int);
            // Return objects that are within range of a position
            std::vector<std::shared_ptr<Object>> getObjectsIn(Vector<int>, int xRange, int yRange);

        private:
            static const SDL_Keycode JUMP_KEY = SDLK_SPACE;
            static const SDL_Keycode SHOOT_KEY = SDLK_RETURN;

            static const int CURSOR_SIZE = 20;
            Vector<int> cursor {0, -CURSOR_SIZE};

            std::map<std::string, bool> keys;

            std::shared_ptr<Robot> robot;
            std::vector<std::shared_ptr<Object>> objects;
            Level level;
            Background bg;
            HighScore highScore;

            State state = STOP;
            std::unique_ptr<Menu> menu;
            int bgCh = -1;

            int tick = 0;
            int score = 0;

            void processEvents();
            void doTick();
            void draw();
            void reset();
    };
};

#endif
