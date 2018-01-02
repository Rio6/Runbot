/*
 * Author: Rio
 * Date: 2017/12/19
 */

#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <memory>
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

                std::shared_ptr<Object> create(Game*);
        };

        extern const std::vector<std::vector<ObjectInfo>> PATTERNS;
        std::vector<std::shared_ptr<runbot::Object>> genLevel(Game*);
    };
};

#endif