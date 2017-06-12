#ifndef _PHYSIC_H_
#define _PHYSIC_H_

namespace runbot {
    class Vector {
        public:
            Vector() : x(0), y(0) {}
            Vector(int x, int y) : x(x), y(y) {}
            int x;
            int y;
    };
};

#endif
