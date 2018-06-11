/*
 * Generates level from a file
 * Randomly select a pattern in the file to generate
 *
 * Author: Rio
 * Date: 2018/12/19
 */

#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <vector>
#include <string>
#include <utility>

#include "object.hpp"
#include "tile.hpp"
#include "vector.hpp"

namespace runbot {
    class Game; // Forward declare

    class Level {
        public:
            Level(Game*);
            // Generates level and put objects in game
            void genLevel(int distance);
            void reset();

        private:
            // Stores info about an object
            class ObjectInfo {
                public:
                    ObjectInfo(Vector<int>, Object::Type);
                    ObjectInfo(int, int, const std::string& type);

                    // Create an object from the info
                    Object *create(Game*, int);
                private:
                    Vector<int> pos;
                    Object::Type type;
            };

            static const char *FILE_PATH;

            std::vector<std::pair<std::vector<ObjectInfo>, int>> patterns;
            Game *game;

            int lastDist = 0;
            int pattSize = 0;
    };
};

#endif
