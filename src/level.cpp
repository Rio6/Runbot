/*
 * Author: Rio
 * Date: 2017/12/19
 */

#include <memory>
#include <vector>
#include <cstdlib>

#include "level.hpp"
#include "game.hpp"
#include "object.hpp"

using namespace runbot;

const std::vector<std::vector<level::ObjectInfo>> level::PATTERNS = {
    {
        ObjectInfo {{Tile::W * 0, Game::H - Tile::H}, Object::TILE},
        ObjectInfo {{Tile::W * 1, Game::H - Tile::H}, Object::TILE},
        ObjectInfo {{Tile::W * 2, Game::H - Tile::H}, Object::TILE},
        ObjectInfo {{Tile::W * 3, Game::H - Tile::H}, Object::TILE},
        ObjectInfo {{Tile::W * 3, Game::H - Tile::H * 2}, Object::TILE},
        ObjectInfo {{Tile::W * 6, Game::H - Tile::H}, Object::TILE},
        ObjectInfo {{Tile::W * 6, Game::H - Tile::H * 2}, Object::TILE},
        ObjectInfo {{Tile::W * 7, Game::H - Tile::H}, Object::TILE},
        ObjectInfo {{Tile::W * 8, Game::H - Tile::H}, Object::TILE},
        ObjectInfo {{Tile::W * 9, Game::H - Tile::H}, Object::TILE}
    },
    {
        ObjectInfo {{Tile::W * 0, Game::H - Tile::H}, Object::TILE},
        ObjectInfo {{Tile::W * 1, Game::H - Tile::H}, Object::TILE},
        ObjectInfo {{Tile::W * 1, Game::H - Tile::H * 2}, Object::TILE},
        ObjectInfo {{Tile::W * 2, Game::H - Tile::H}, Object::TILE},
        ObjectInfo {{Tile::W * 2, Game::H - Tile::H * 2}, Object::TILE},
        ObjectInfo {{Tile::W * 2, Game::H - Tile::H * 3}, Object::TILE},
        ObjectInfo {{Tile::W * 3, Game::H - Tile::H * 3}, Object::TILE},
        ObjectInfo {{Tile::W * 4, Game::H - Tile::H * 3}, Object::TILE},
        ObjectInfo {{Tile::W * 5, Game::H - Tile::H * 3}, Object::TILE},
        ObjectInfo {{Tile::W * 7, Game::H - Tile::H}, Object::TILE},
        ObjectInfo {{Tile::W * 7, Game::H - Tile::H * 5}, Object::TILE},
        ObjectInfo {{Tile::W * 8, Game::H - Tile::H}, Object::TILE},
        ObjectInfo {{Tile::W * 9, Game::H - Tile::H}, Object::TILE}
    }
};

std::shared_ptr<runbot::Object> level::ObjectInfo::create(Game *game) {
    if(type == Object::TILE) {
        return std::shared_ptr<Object>(new Tile(game,
                    pos.x + game->distance + Game::W, pos.y,
                    Tile::TILE_GROUND));
    }
    return nullptr;
}

std::vector<std::shared_ptr<Object>> level::genLevel(Game *game) {
    std::vector<std::shared_ptr<Object>> objects;
    if(game->distance % 1000 == 0) {
        for(ObjectInfo info : PATTERNS[std::rand() % PATTERNS.size()]) {
            objects.push_back(info.create(game));
        }
    }
    return objects;
}
