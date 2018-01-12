/*
 * Author: Rio
 * Date: 2018/1/12
 */

#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <vector>

#include "object.hpp"
#include "tile.hpp"
#include "vector.hpp"

namespace runbot {
    class Game; // Forward declare

    namespace level {
        const int LENGTH = 1000;

        class ObjectInfo {
            public:
                Vector<int> pos;
                Object::Type type;

                Object *create(Game*, int);
        };

        extern const std::vector<std::vector<ObjectInfo>> PATTERNS;
        void genLevel(Game*, int);
    };
};

#endif
