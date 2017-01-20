#ifndef _GAME_H_
#define _GAME_H_

#include "graphic.hpp"

class Game {
    public:
        Game();
        ~Game();

        void loop();

    private:
        Graphic graphic;
        bool running;

        void processEvents();
};

#endif
