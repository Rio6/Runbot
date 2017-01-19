#ifndef _MAIN_H_
#define _MAIN_H_

#include <iostream>

namespace config {
    const int WIN_W = 400;
    const int WIN_H = 300;
    const std::string NAME = "Runbot";
    const int FPS = 60;
    const int TPF = 1000 / FPS; // ticks per frame
};

#endif
