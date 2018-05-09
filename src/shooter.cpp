/*
 * Author: Rio
 * Date: 2018/05/04
 */

#include "shooter.hpp"
#include "object.hpp"
#include "game.hpp"
#include "collision.hpp"
#include "explosion.hpp"
#include "bullet.hpp"
#include "vector.hpp"

using runbot::Shooter;

Shooter::Shooter(Game *game, Vector<int> pos) :
    Object(pos, {pos, pos + Vector<int>{Shooter::W, Shooter::H}, speed}),
    game(game),
    bodyAnim(0, 0, 200, 300, 120, 2, true),
    armAnim(0, 300, 200, 300, 30, 20, false), spawnTime(game->tick) {

    for(auto &object : game->getObjectsIn({game->distance, 0}, Game::W, Game::H)) {
        if(object->getType() == SHOOTER) {
            dead = true;
        }
    }

    bodyAnim.start();
}

void Shooter::draw() {
    Graphic &graphic = Graphic::instance();
    SDL_Rect src, des;

    // Body animation
    src = bodyAnim.getCurrentClip();
    des = {pos.x - game->distance, pos.y - game->cameraY, Shooter::W, Shooter::H};
    graphic.renderImage("shooter.png", &src, &des);

    // Arm animation
    src = armAnim.getCurrentClip();
    des = {pos.x - game->distance, pos.y - game->cameraY, Shooter::W, Shooter::H};
    graphic.renderImage("shooter.png", &src, &des);
}

void Shooter::doTick(int tick) {

    if(game->distance + Game::W - Shooter::W >= pos.x) {
        if(game->distance + Game::W - Shooter::W * 3 >= pos.x)
            speed.x = game->speed * 1.2;
        else if(game->distance + Game::W - Shooter::W * 2 <= pos.x)
            speed.x = game->speed * 0.8;

        if((tick + spawnTime) % 180 == 0) {
            game->spawn(new Bullet(game, {pos.x, pos.y + 90}, game->speed, true));
            armAnim.start();
        }
    }

    // Hover 10 units above the highest tile
    int highestY = Game::H;
    auto objects = game->getObjectsIn(pos, 300, Game::H); // objects are std::vector of std::shared_ptr of Object
    for(auto &object : objects) {
        if(object->getType() == TILE) {
            Vector<int> objPos = object->getPos();
            if(objPos.y < highestY)
                highestY = objPos.y;
        }
    }

    if(highestY < pos.y + Shooter::H + 10) {
        speed.y = -game->speed;
    } else if(highestY > pos.y + Shooter::H + 15) {
        speed.y = game->speed;
    } else {
        speed.y = 0;
    }

    pos += speed;

    hitbox.speed = speed;
    hitbox.minPos = pos + Vector<int>{0, 0};
    hitbox.maxPos = pos + Vector<int>{Shooter::W, Shooter::H};

    if(hp <= 0) {
        game->spawn(new Explosion(game, pos, {Shooter::W, Shooter::H}));
        dead = true;
    }

    bodyAnim.doTick();
    armAnim.doTick();
}

bool Shooter::onCollide(Object& other, Direction dir) {
    switch(other.getType()) {
        case BULLET:
            if(!dynamic_cast<Bullet&>(other).isEnemy())
                hp--;
            break;
        default:
            break;
    }

    return true;
}

bool Shooter::isDead() {
    return dead;
}

runbot::Object::Type Shooter::getType() {
    return SHOOTER;
}
