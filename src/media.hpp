/*
 * Author: Rio
 * Date: 2018/06/23
 */

#ifndef _MEDIA_H_
#define _MEDIA_H_

#include <string>
#include <map>

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

namespace runbot {
    class Media {
        public:
            static Media &instance();
            static void reset();
            template<typename T> static T get(const std::string&);

        private:
            static Media *media;

            Media();
            ~Media();

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
                {"missile.wav", nullptr}
            };
    };

    template<> SDL_Texture *Media::get<SDL_Texture*>(const std::string&);
    template<> Mix_Chunk *Media::get<Mix_Chunk*>(const std::string&);
};

#endif
