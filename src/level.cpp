/*
 * Author: Rio
 * Date: 2018/1/12
 */

#include <vector>
#include <cstdlib>

#include "level.hpp"
#include "game.hpp"
#include "object.hpp"
#include "tile.hpp"
#include "missile.hpp"
#include "vector.hpp"

using runbot::Level;

const std::vector<std::vector<Level::ObjectInfo>> Level::PATTERNS = {
    {
        {{Tile::W * 0, Game::H - Tile::H}, Object::TILE},
        {{Tile::W * 1, Game::H - Tile::H}, Object::TILE},
        {{Tile::W * 2, Game::H - Tile::H}, Object::TILE},
        {{Tile::W * 3, Game::H - Tile::H}, Object::TILE},
        {{Tile::W * 3, Game::H - Tile::H * 2}, Object::TILE},
        {{Tile::W * 6, Game::H - Tile::H}, Object::TILE},
        {{Tile::W * 6, Game::H - Tile::H * 2}, Object::TILE},
        {{Tile::W * 7, Game::H - Tile::H}, Object::TILE},
        {{Tile::W * 8, Game::H - Tile::H}, Object::TILE},
        {{Tile::W * 9, Game::H - Tile::H}, Object::TILE},
        {{0, Game::H - 370}, Object::MISSILE}
    },
    {
        {{Tile::W * 0, Game::H - Tile::H}, Object::TILE},
        {{Tile::W * 1, Game::H - Tile::H}, Object::TILE},
        {{Tile::W * 1, Game::H - Tile::H * 2}, Object::TILE},
        {{Tile::W * 2, Game::H - Tile::H}, Object::TILE},
        {{Tile::W * 2, Game::H - Tile::H * 2}, Object::TILE},
        {{Tile::W * 2, Game::H - Tile::H * 3}, Object::TILE},
        {{Tile::W * 3, Game::H - Tile::H * 3}, Object::TILE},
        {{Tile::W * 4, Game::H - Tile::H * 3}, Object::TILE},
        {{Tile::W * 5, Game::H - Tile::H * 3}, Object::TILE},
        {{Tile::W * 7, Game::H - Tile::H}, Object::TILE},
        {{Tile::W * 7, Game::H - Tile::H * 5}, Object::TILE},
        {{Tile::W * 8, Game::H - Tile::H}, Object::TILE},
        {{Tile::W * 9, Game::H - Tile::H}, Object::TILE}
    },
};

Level::Level(Game *game) : game(game) {
}

void Level::genLevel(int distance) {
    if(distance - lastDist > Level::LENGTH) {
        distance = lastDist + Level::LENGTH;
        for(ObjectInfo info : PATTERNS[std::rand() % PATTERNS.size()]) {
            game->spawn(info.create(game, distance));
        }
        lastDist = distance;
    }
}

runbot::Object *Level::ObjectInfo::create(Game *game, int distance) {
    switch(type) {
        case Object::TILE:
            return new Tile(game,
                    {pos.x + distance, pos.y},
                    Tile::TILE_GROUND);
        case Object::MISSILE:
            return new Missile(game,
                    {pos.x + distance, pos.y});
        default:
            return nullptr;
    }
}
