/*
 * Author: Rio
 * Date: 2017/05/21
 */

#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_

#define USE_VSYNC

#include <string>
#include <map>

#include "SDL.h"

namespace runbot {

    class Graphic {
        public:
            static Graphic &instance();

            void renderImage(const std::string& name,
                    const SDL_Rect* src, const SDL_Rect* des, int color = 0xffffff);
            void renderText(const std::string &text, const SDL_Rect *des, int color = 0xffffff);
            void clear();
            void update();

        private:
            SDL_Renderer *rend;
            SDL_Window *win;

            std::map<std::string, SDL_Texture*> imgs {
                {"robot.png", nullptr},
                {"tiles.png", nullptr},
                {"missile.png", nullptr},
                {"bullet.png", nullptr},
                {"bg.png", nullptr},
                {"cursor.png", nullptr},
                {"letters.png", nullptr},
                {"explosion.png", nullptr},
                {"pause.png", nullptr}
            };

            std::map<char, SDL_Rect> letters;

            Graphic();
            ~Graphic();
            void loadImages();
    };
};

#endif
