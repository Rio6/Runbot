/*
 * Author: Rio
 * Date: 2017/11/29
 */

#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_

//#define USE_VSYNC

#include <string>
#include <map>

#include "SDL2/SDL.h"

namespace runbot {

    static const std::string ROBOT_IMG = "robot.png";
    static const std::string TILE_IMG = "tiles.png";
    static const std::string BG_IMG = "bg.png";

    class Graphic {
        public:
            static Graphic &instance();

            void renderImage(const std::string&,
                    const SDL_Rect*, const SDL_Rect*);
            void clear();
            void update();

        private:
            SDL_Renderer *rend;
            SDL_Window *win;
            std::map<std::string, SDL_Texture*> imgs = {
                {ROBOT_IMG, nullptr},
                {TILE_IMG, nullptr},
                {BG_IMG, nullptr}
            };;

            Graphic();
            ~Graphic();
            void loadImages();
    };
};

#endif
