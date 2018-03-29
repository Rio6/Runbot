/*
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
            void genLevel(int distance);
            void reset();

        private:
            class ObjectInfo {
                public:
                    ObjectInfo(Vector<int>, Object::Type);
                    ObjectInfo(int, int, const std::string& type);

                    Object *create(Game*, int);
                private:
                    Vector<int> pos;
                    Object::Type type;
            };

            const std::string FILE_PATH = "assets/levels.json";

            std::vector<std::pair<std::vector<ObjectInfo>, int>> patterns;
            Game *game;

            int lastDist = 0;
            int pattSize = 1000;
    };
};

#endif
