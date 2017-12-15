/*
 * Author: Rio
 * Date: 2017/12/08
 */

#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

namespace runbot {
    class Background {
        public:
            Background();
            ~Background();

            void doTick();
            void draw();
        private:
            static const int W = 500;
            static const int H = 400;
            int pos;
    };
};
#endif
