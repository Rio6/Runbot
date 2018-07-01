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

const float Shooter::SPEED_FACTOR = 10;

Shooter::Shooter(Game *game, Vector<int> pos) :
    Object(pos, {game->speed, 0}, {.minPos = pos, .maxPos = pos + Vector<int>{Shooter::W, Shooter::H}}),
    game(game),
    bodyAnim(0, 0, 200, 300, 120, 2, true),
    armAnim(0, 300, 200, 300, 30, 20, false) {

    for(auto &object : game->getObjectsIn({game->distance + Game::W, 0}, Game::W, Game::H)) {
        if(object->getType() == SHOOTER) {
            dead = true;
        }
    }

    bodyAnim.start();
}

void Shooter::draw() {
    Graphic &graphic = Graphic::instance();
    SDL_Rect src, des = {pos.x - game->distance, pos.y - game->cameraY, Shooter::W, Shooter::H};

    // Body animation
    src = bodyAnim.getCurrentClip();
    graphic.renderImage("shooter.png", &src, &des);

    // Arm animation
    src = armAnim.getCurrentClip();
    graphic.renderImage("shooter.png", &src, &des);
}

void Shooter::doTick(int tick) {

    // Set spawn time at the first tick
    if(!spawnTime) spawnTime = tick;

    // Shoot bullet every 180 ticks
    if((tick + spawnTime) % 180 == 0) {
        game->spawn(new Bullet(game, {pos.x, pos.y + 90}, game->speed, true));
        armAnim.start();
    }

    // Move around
    if(game->distance + Game::W - Shooter::W * 3 >= pos.x &&
            speed.x < game->speed * 1.2)
        speed.x += (game->speed * 1.2 - speed.x) / SPEED_FACTOR;
    else if(game->distance + Game::W - Shooter::W * 2 <= pos.x &&
            speed.x > game->speed * .8)
        speed.x += (game->speed * .8 - speed.x) / SPEED_FACTOR;

    // Hover above the highest tile
    int highestY = Game::H;
    auto objects = game->getObjectsIn({pos.x + 150, pos.y}, 150, Game::H); // objects is std::vector<std::shared_ptr<Object>>
    for(auto &object : objects) {
        if(object->getType() == TILE) {
            Vector<int> objPos = object->getPos();
            if(objPos.y < highestY)
                highestY = objPos.y;
        }
    }

    int diff = highestY - (pos.y + Shooter::H + 20);
    if(diff < 0) {
        if(speed.y > 0 || (diff < -10 && speed.y > -game->speed))
            speed.y -= game->speed / SPEED_FACTOR;
    } else if(diff > 0) {
        if(speed.y < 0 || (diff > 10 && speed.y < game->speed))
            speed.y += game->speed / SPEED_FACTOR;
    }

    pos += speed;

    hitbox.speed = speed;
    hitbox.minPos = pos + Vector<int>{0, 0};
    hitbox.maxPos = pos + Vector<int>{Shooter::W, Shooter::H};

    if(hp <= 0) {
        game->addScore(Shooter::SCORE);
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
            else return false;
            break;
        default:
            break;
    }

    return true;
}

bool Shooter::isDead() {
    return dead || pos.x + Shooter::W - game->distance < 0;
}

runbot::Object::Type Shooter::getType() {
    return SHOOTER;
}
