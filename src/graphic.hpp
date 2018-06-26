/*
 * Wrapper for SDL functions
 *
 * Author: Rio
 * Date: 2017/05/21
 */

#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_

#include <string>
#include <map>

#include "SDL.h"

namespace runbot {

    // Class graphics
    class Graphic {
        public:
            static Graphic &instance();
            static void reset();

            SDL_Renderer *getRenderer();
            void renderImage(const std::string &name,
                    const SDL_Rect* src, const SDL_Rect* des, int color = 0xffffff);
            void renderText(const std::string &text, const SDL_Rect *des, int color = 0x000000);
            void clear();
            void update();

        private:
            static Graphic *graphic;

            SDL_Renderer *rend;
            SDL_Window *win;

<<<<<<< HEAD
            // Images to load
            std::map<std::string, SDL_Texture*> imgs {
                {"robot.png", nullptr},
                {"tiles.png", nullptr},
                {"missile.png", nullptr},
                {"bullet.png", nullptr},
                {"bg.png", nullptr},
                {"cursor.png", nullptr},
                {"letters.png", nullptr},
                {"explosion.png", nullptr},
                {"pause.png", nullptr},
                {"menu.png", nullptr},
                {"shooter.png", nullptr}
            };

            // Sounds to load
            std::map<std::string, Mix_Chunk*> sounds {
                {"bullet.wav", nullptr},
                {"bullet_hit.wav", nullptr},
                {"explosion.wav", nullptr},
                {"button.wav", nullptr},
                {"missile.wav", nullptr},
                {"missile_end.wav", nullptr},
                {"missile_start.wav", nullptr}
            };

            std::map<char, SDL_Rect> letters;

=======
>>>>>>> master
            Graphic();
            ~Graphic();

            std::map<char, SDL_Rect> letters;
    };
};

#endif
