/*
 * Wrapper for SDL functions
 * It's called Graphic but there are sound functions in here too
 *
 * Author: Rio
 * Date: 2017/05/21
 */

#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_

#define USE_VSYNC

#include <string>
#include <map>

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

namespace runbot {

    // Class for graphics and audio
    // I put audio here because it kind of fits here
    class Graphic {
        public:
            static Graphic &instance();
            static void reset();

            void renderImage(const std::string& name,
                    const SDL_Rect* src, const SDL_Rect* des, int color = 0xffffff);
            void renderText(const std::string &text, const SDL_Rect *des, int color = 0xffffff);
            int playSound(const std::string& name, int repeat = 0, int channel = -1);
            void stopSound(int channel);
            bool soundPlaying(int channel);
            void clear();
            void update();

        private:
            static Graphic *graphic;

            SDL_Renderer *rend;
            SDL_Window *win;

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

            Graphic();
            ~Graphic();
            void loadMedia();
    };
};

#endif
