#ifndef _MAIN_H_
#define _MAIN_H_

inline namespace config {
    const int WIN_W = 400;
    const int WIN_H = 300;
    const char *const NAME = "Runbot";
    const int FPS = 60;
    const int TPF = 1000 / FPS; // ticks per frame
};

void logError(const char *msg, const char* err);

#endif
