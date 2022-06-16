#include "bullet.h"
#include <cmath>

Bullet::Bullet()
{
    this->speed_y = 0;
}

void Bullet::SetSpeed(double sx, double sy){
    this->speed_x = sx;
    this->speed_y = sy;
}

void Bullet::Shoot(double elapsed){
    this->move(0, this->speed_y*elapsed);
}

void Bullet::ShootLeft(double elapsed, Player &player){
    this->setPosition(player.getPosition().x - 30, player.getPosition().y - 40);
    this->Shoot(elapsed);
}

void Bullet::ShootRight(double elapsed, Player &player){
    this->setPosition(player.getPosition().x + 30, player.getPosition().y - 40);
    this->Shoot(elapsed);
}

void Bullet::ShootLaser(double elapsed, DeathStar &deathstar){
    this->setPosition(deathstar.getPosition().x + 40, deathstar.getPosition().y - 40);
    this->Shoot(elapsed);
}
