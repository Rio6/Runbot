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
            Game *game;
            SDL_Rect startBtn;
    };

    class PauseMenu {
        public:
            PauseMenu(Game*);
            void onClick(Vector<int>&);
            void draw();
        private:
            SDL_Rect resumeBtn;
            SDL_Rect quitBtn;
    };
};

#endif
