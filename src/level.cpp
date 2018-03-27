/*
 * Author: Rio
 * Date: 2017/12/19
 */

#include <vector>
#include <cstdlib>
#include <fstream>
#include <string>

#include "nlohmann/json.hpp"

#include "level.hpp"
#include "game.hpp"
#include "object.hpp"
#include "tile.hpp"
#include "missile.hpp"
#include "vector.hpp"

using runbot::Level;
using nlohmann::json;

Level::Level(Game *game) : game(game) {

    // Load level patterns from file
    std::ifstream lvlFile;
    lvlFile.open(Level::FILE_PATH);

    if(!lvlFile) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Cannot load %s", FILE_PATH.c_str());
    } else {
        try {
            json lvlJson;
            lvlFile >> lvlJson;

            for(json pattJson : lvlJson["patterns"]) {
                std::vector<ObjectInfo> objects;

                for(json objJson : pattJson["objects"]) {
                    int x = objJson["x"], y = objJson["y"];
                    std::string type = objJson["type"];

                    objects.emplace_back(x, y, type);
                }

                patterns.push_back(objects);
            }
        } catch(json::exception& e) {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to parse level file: %s", e.what());
        }
    }
}

void Level::genLevel(int distance) {
    if(patterns.size() <= 0) return;

    if(distance - lastDist > Level::LENGTH) {
        distance = lastDist + Level::LENGTH;
        for(ObjectInfo info : patterns[std::rand() % patterns.size()]) {
            game->spawn(info.create(game, distance));
        }
        lastDist = distance;
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
    else
        this->type = Object::UNKNOWN;
}

runbot::Object *Level::ObjectInfo::create(Game *game, int distance) {
    Vector<int> tgtPos = {pos.x + distance, pos.y};
    switch(type) {
        case Object::TILE:
            return new Tile(game, tgtPos, Tile::TILE_GROUND);
        case Object::MISSILE:
            return new Missile(game, tgtPos);
        default:
            return nullptr;
    }
}

void Level::reset() {
    lastDist = 0;
}
