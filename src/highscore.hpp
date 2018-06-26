/*
 * Author: Rio
 * Date: 2018/06/25
 */

#ifndef _HIGHSCORE_H_
#define _HIGHSCORE_H_

#include <memory>

namespace runbot {
    class HighScore {
        public:
            HighScore();
            ~HighScore();
            int getScore();
            void updateScore(int);
        private:
            char *scorePath = nullptr;
            int hiScore = 0;

            void save();
            void load();
    };
};

#endif
