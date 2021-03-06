/*
 * Author: Rio
 * Date: 2018/02/11
 */

#ifndef _MENU_H_
#define _MENU_H_

#include "SDL.h"
#include "vector.hpp"

namespace runbot {
    class Game; //Forward declare

    class Menu {
        public:
            class MenuRect : public SDL_Rect {
                public:
                    enum State {
                        UP, DOWN
                    } state = UP;

                    MenuRect(int, int, int, int);
                    // Return true when clicked
                    bool onMouse(Vector<int> &pos, bool down);

                private:
                    bool inRect(const Vector<int>&);
            };

            virtual bool onMouse(Vector<int> &pos, bool down) = 0;
            virtual void draw() = 0;
    };

    class StartMenu : public Menu {
        public:
            StartMenu(Game*, int hiScore);
            bool onMouse(Vector<int> &pos, bool down);
            void draw();
        private:
            Game *game;
            int hiScore;

            MenuRect bgRect;
            MenuRect titleRect;
            MenuRect startBtn;
            MenuRect verRect;
            MenuRect scoreRect;
    };

    class PauseMenu : public Menu {
        public:
            PauseMenu(Game*);
            bool onMouse(Vector<int> &pos, bool down);
            void draw();
        private:
            Game *game;

            MenuRect bgRect;
            MenuRect titleRect;
            MenuRect resumeBtn;
            MenuRect menuBtn;
    };

    class DeadMenu : public Menu {
        public:
            DeadMenu(Game*, int score, int hiScore);
            bool onMouse(Vector<int> &pos, bool down);
            void draw();
        private:
            Game *game;
            int score;
            int hiScore;

            MenuRect bgRect;
            MenuRect titleRect;
            MenuRect restartBtn;
            MenuRect menuBtn;
            MenuRect scoreRect;
            MenuRect hiScoreRect;
    };

    class GameMenu : public Menu {
        public:
            GameMenu(Game*);
            bool onMouse(Vector<int> &pos, bool down);
            void draw();
        private:
            Game *game;
            MenuRect pauseBtn;
    };
};

#endif
