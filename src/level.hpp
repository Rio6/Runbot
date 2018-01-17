/*
 * Author: Rio
 * Date: 2018/12/19
 */

#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <vector>

#include "object.hpp"
#include "tile.hpp"
#include "vector.hpp"

namespace runbot {
    class Game; // Forward declare

    class Level {
        public:
            static const int LENGTH = 1000;

            Level(Game*);
            void genLevel(int);

        private:
            class ObjectInfo {
                public:
                    Vector<int> pos;
                    Object::Type type;

                    Object *create(Game*, int);
            };

            static const std::vector<std::vector<ObjectInfo>> PATTERNS;
            Game *game;
            int lastDist = 0;
    };
};

#endif
