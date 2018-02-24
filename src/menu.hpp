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

    class Menu {
        public:
            virtual void onClick(Vector<int> &pos) = 0;
            virtual void draw() = 0;
        protected:
            bool inRect(const SDL_Rect&, const Vector<int>&);
    };

    class StartMenu : public Menu {
        public:
            StartMenu(Game*);
            void onClick(Vector<int> &pos);
            void draw();
        private:
            static const SDL_Rect TITLE_RECT;
            static const SDL_Rect START_BTN;

            Game *game;
    };

    class PauseMenu : public Menu {
        public:
            PauseMenu(Game*);
            void onClick(Vector<int> &pos);
            void draw();
        private:
            static const SDL_Rect TITLE_RECT;
            static const SDL_Rect RESUME_BTN;
            static const SDL_Rect MENU_BTN;

            Game *game;
    };

    class DeadMenu : public Menu {
        public:
            DeadMenu(Game*);
            void onClick(Vector<int> &pos);
            void draw();
        private:
            static const SDL_Rect TITLE_RECT;
            static const SDL_Rect MENU_BTN;

            Game *game;
    };
};

#endif
