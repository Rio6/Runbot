/*
 * Author: Rio
 * Date: 2017/09/22
 */

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "SDL2/SDL.h"

namespace runbot {
    class Object {
        public:
            virtual ~Object() {};
            virtual void draw(SDL_Renderer*, SDL_Texture*) = 0;
            virtual void doTick(int, int) = 0;
            virtual int getX() = 0;
            virtual int getY() = 0;
    };
};

#endif
