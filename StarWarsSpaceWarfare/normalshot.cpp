#include "normalshot.h"
#include <iostream>

NormalShot::NormalShot(sf::Texture &texture){
    this->SetSpeed(0, -700);

    setTexture(texture);
    setScale(0.5,0.5);
}

void NormalShot::ShootLeft(Player &player){
    this->setPosition(player.getPosition().x - 33, player.getPosition().y - 20);
}

void NormalShot::ShootRight(Player &player){
    this->setPosition(player.getPosition().x + 25, player.getPosition().y - 20);
}

void NormalShot::ShootLaser(DeathStar &deathstar){
    this->setPosition(deathstar.getPosition().x + 44, deathstar.getPosition().y + 40);
}
