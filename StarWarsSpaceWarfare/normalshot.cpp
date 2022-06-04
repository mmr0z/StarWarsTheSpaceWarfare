#include "normalshot.h"
#include <iostream>

NormalShot::NormalShot(sf::Texture &texture){
    this->SetSpeed(0, -700);

    setTexture(texture);
    setScale(0.5,0.5);
}

void NormalShot::ShootLeft(Player &player){
    setPosition(player.getPosition().x - 33, player.getPosition().y - 20);
}

void NormalShot::ShootRight(Player &player){
    setPosition(player.getPosition().x + 25, player.getPosition().y - 20);
}
