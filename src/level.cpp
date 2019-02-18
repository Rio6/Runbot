/*
 * Author: Rio
 * Date: 2017/12/19
 */

#include <vector>
#include <cstdlib>
#include <string>
#include <utility>

#include "SDL_platform.h"

#ifdef __IPHONEOS__
#include "json.hpp"
#else
#include "nlohmann/json.hpp"
#endif

#include "level.hpp"
#include "game.hpp"
#include "object.hpp"
#include "tile.hpp"
#include "missile.hpp"
#include "shooter.hpp"
#include "vector.hpp"

#include "config.h"

using runbot::Level;
using nlohmann::json;

const char *Level::FILE_PATH = DATA_DIR "levels.json";

Level::Level(Game *game) : game(game) {

    // Load levels from file
    SDL_RWops *lvlFile = SDL_RWFromFile(Level::FILE_PATH, "r");
    if(!lvlFile) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Cannot load %s", FILE_PATH);
    } else {
        int size = SDL_RWsize(lvlFile);
        // File code from https://gitlab.com/wikibooks-opengl/modern-tutorials/blob/master/common-sdl2/shader_utils.cpp
        char content[size + 1];
        char *buff = content;

        int read = 1, readTotal = 0;
        while(read < size && read != 0) {
            read = SDL_RWread(lvlFile, buff, 1, (size - readTotal));
            readTotal += read;
            buff += read;
        }

        content[readTotal] = '\0';

        // Parse the content
        try {
            json rootJson = json::parse(content);

            for(json lvlJson : rootJson["levels"]) {
                std::vector<ObjectInfo> objInfos;

                int size = lvlJson["size"];

                for(json objJson : lvlJson["objects"]) {
                    int x = objJson["x"], y = objJson["y"];
                    std::string type = objJson["type"];

                    objInfos.emplace_back(x, y, type);
                }

                levels.emplace_back(objInfos, size);
            }
        } catch(json::exception& e) {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to parse level file: %s", e.what());
            levels.clear();
        }

        SDL_RWclose(lvlFile);
    }
}

// Generates level and put objects in game
// Only generates if the distance is after the end of the last generated level
void Level::genLevel(int distance) {
    if(levels.size() <= 0) return;

    if(distance == 0) {
        // Put some tiles at the beginning
        int c = 0;
        for(int i = 0; i < Game::W - Tile::W; i += Tile::W, c++) {
            game->spawn(new Tile(game,
                        {i, Game::H - Tile::H}));
        }
        lastDist = 0;
        lvlSize = Tile::W * c;
    }

    if(distance - lastDist > lvlSize) {
        distance = lastDist + lvlSize;

        // Get a non repeating random index
        int index = 0;
        if(levels.size() > 1) {
            while((index = std::rand() % levels.size()) == lastInd);
            lastInd = index;
        }

        // Get the level
        const auto &[objects, size] = levels[index];

        // Create the objects
        for(ObjectInfo info : objects) {
            game->spawn(info.create(game, distance));
        }
        lastDist = distance;
        lvlSize = size;
    }
}

Level::ObjectInfo::ObjectInfo(Vector<int> pos, Object::Type type) : pos(pos), type(type) {
}

Level::ObjectInfo::ObjectInfo(int x, int y, const std::string &type) {
    this->pos = {x, y};

    if(type == "ROBOT")
        this->type = Object::ROBOT;
    else if(type == "TILE")
        this->type = Object::TILE;
    else if(type == "MISSILE")
        this->type = Object::MISSILE;
    else if(type == "BULLET")
        this->type = Object::BULLET;
    else if(type == "EXPLOSION")
        this->type = Object::EXPLOSION;
    else if(type == "SHOOTER")
        this->type = Object::SHOOTER;
    else
        this->type = Object::UNKNOWN;
}

// Create an object from the info
runbot::Object *Level::ObjectInfo::create(Game *game, int distance) {
    Vector<int> tgtPos = {pos.x + distance, pos.y};
    switch(type) {
        case Object::TILE:
            return new Tile(game, tgtPos);
        case Object::MISSILE:
            return new Missile(game, tgtPos);
        case Object::SHOOTER:
            return new Shooter(game, tgtPos);
        default:
            return nullptr;
    }
}

void Level::reset() {
    lastDist = 0;
}
