/*
 * Author: Rio
 * Date: 2018/06/25
 */

#if defined(unix) || defined(__unix__) || defined(__unix)
#include <cstdio>
#include <cerrno>
#include <sys/stat.h>
#endif

#include <string>
#include <cstdlib>
#include <cstring>

#include "SDL.h"

#include "highscore.hpp"
#include "game.hpp"

using runbot::HighScore;

HighScore::HighScore() {

    char *scoreDir = nullptr;

#if defined(unix) || defined(__unix__) || defined(__unix)
    // I want to put stuff under $HOME/.Runbot in unix systems
    char *home = std::getenv("HOME");
    if(home) {
        scoreDir = (char*) SDL_malloc(std::strlen(home) + std::strlen(NAME) + 4); // 4 is '/' '.' '/' '\0'
        std::sprintf(scoreDir, "%s/.%s/", home, NAME);
        if(mkdir(scoreDir, 0700) != 0 && errno != EEXIST) {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Can't create %s: %s", scoreDir, std::strerror(errno));
            SDL_free(scoreDir);
            scoreDir = nullptr;
        }
    }
#else
    scoreDir = SDL_GetPrefPath(NULL, NAME);
#endif

    if(scoreDir) {
        scorePath = new char[std::strlen(scoreDir) + 10]; // 10 is "highscore" and '\0'
        std::sprintf(scorePath, "%shighScore", scoreDir);
        SDL_free(scoreDir);
        scoreDir = nullptr;
    }

    load();
}

HighScore::~HighScore() {
    delete scorePath;
    scorePath = nullptr;
}

int HighScore::getScore() {
    return hiScore;
}

void HighScore::updateScore(int score) {
    if(score > hiScore) {
        hiScore = score;
        save();
    }
}

void HighScore::save() {
    if(!scorePath) return;

    SDL_RWops *file = SDL_RWFromFile(scorePath, "w");
    if(!file) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Cannot load %s", scorePath);
    } else {
        std::string scoreStr = std::to_string(hiScore) + "\n";
        SDL_RWwrite(file, scoreStr.c_str(), sizeof(char), scoreStr.size());
        SDL_RWclose(file);
    }
}

void HighScore::load() {
    if(!scorePath) return;

    SDL_RWops *file = SDL_RWFromFile(scorePath, "r");
    if(!file) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Cannot load %s", scorePath);
    } else {
        int size = SDL_RWsize(file);
        // File code from https://gitlab.com/wikibooks-opengl/modern-tutorials/blob/master/common-sdl2/shader_utils.cpp
        char content[size + 1];
        char *buff = content;

        int read = 1, readTotal = 0;
        while(read < size && read != 0) {
            read = SDL_RWread(file, buff, 1, (size - readTotal));
            readTotal += read;
            buff += read;
        }

        content[readTotal] = '\0';

        hiScore = std::atoi(content);

        SDL_RWclose(file);
    }
}
