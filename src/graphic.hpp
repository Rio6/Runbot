/*
 * Author: Rio
 * Date: 2018/1/3
 */

#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_

#define USE_VSYNC

#include <string>
#include <map>

#include "SDL2/SDL.h"

namespace runbot {

    static const std::string ROBOT_IMG = "robot.png";
    static const std::string TILE_IMG = "tiles.png";
    static const std::string MISSILE_IMG = "missile.png";
    static const std::string BULLET_IMG = "bullet.png";
    static const std::string BG_IMG = "bg.png";
    static const std::string CURSOR_IMG = "cursor.png";

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
            std::map<std::string, SDL_Texture*> imgs {
                {ROBOT_IMG, nullptr},
                {TILE_IMG, nullptr},
                {MISSILE_IMG, nullptr},
                {BULLET_IMG, nullptr},
                {BG_IMG, nullptr},
                {CURSOR_IMG, nullptr}
            };;

            Graphic();
            ~Graphic();
            void loadImages();
    };
};

#endif
