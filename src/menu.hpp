/*
 * Author: Rio
 * Date: 2018/02/11
 */

#ifndef _MENU_H_
#define _MENU_H_

#include "SDL2/SDL.h"
#include "vector.hpp"

namespace runbot {
    class Game; //Forward declare

    class StartMenu {
        public:
            StartMenu(Game*);
            void onClick(Vector<int>&);
            void draw();
        private:
            static const int BTN_W = 400;
            static const int BTN_H = 100;
            Game *game;
            SDL_Rect startBtn;
    };

    class PauseMenu {
        public:
            PauseMenu(Game*);
            void onClick(Vector<int>&);
            void draw();
        private:
            static const int BTN_W = 120;
            static const int BTN_H = 80;
            Game *game;
            SDL_Rect resumeBtn;
            SDL_Rect quitBtn;
    };
};

#endif
