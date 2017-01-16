#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_

#include <SDL2/SDL.h>

namespace graphic {
    class Graphic {
        public:
            Graphic();
            ~Graphic();
            int init();
        private:
            SDL_Renderer *rend;
    };
};

#endif
