/*
 * Author: Rio
 * Date: 2017/12/19
 */

#include <vector>
#include <cstdlib>
#include <string>
#include <utility>

#include "nlohmann/json.hpp"

#include "level.hpp"
#include "game.hpp"
#include "object.hpp"
#include "tile.hpp"
#include "missile.hpp"
#include "shooter.hpp"
#include "vector.hpp"

using runbot::Level;
using nlohmann::json;

Level::Level(Game *game) : game(game) {

    // Load level patterns from file
    SDL_RWops *lvlFile = SDL_RWFromFile(Level::FILE_PATH, "r");
    int size = SDL_RWsize(lvlFile);

    if(size < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Cannot load %s", FILE_PATH);
    } else {
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

        try {
            json lvlJson = json::parse(content);

            for(json pattJson : lvlJson["patterns"]) {
                std::vector<ObjectInfo> objects;

                int size = pattJson["size"];

                for(json objJson : pattJson["objects"]) {
                    int x = objJson["x"], y = objJson["y"];
                    std::string type = objJson["type"];

                    objects.emplace_back(x, y, type);
                }

                patterns.emplace_back(objects, size);
            }
        } catch(json::exception& e) {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to parse level file: %s", e.what());
        }
    }

    SDL_RWclose(lvlFile);
}

void Level::genLevel(int distance) {
    if(patterns.size() <= 0) return;

    if(distance - lastDist > pattSize) {
        distance = lastDist + pattSize;
        const auto &[objects, size] = patterns[std::rand() % patterns.size()];
        for(ObjectInfo info : objects) {
            game->spawn(info.create(game, distance));
        }
        lastDist = distance;
        pattSize = size;
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

runbot::Object *Level::ObjectInfo::create(Game *game, int distance) {
    Vector<int> tgtPos = {pos.x + distance, pos.y};
    switch(type) {
        case Object::TILE:
            return new Tile(game, tgtPos, Tile::TILE_GROUND);
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
