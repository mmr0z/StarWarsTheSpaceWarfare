#include "tiefighter.h"

TieFighter::TieFighter(sf::Texture &texture)
{
    this->speed_x = rand()%100 - 50;
    this->speed_y = rand()%5;

    this->hp = 50;

    setTexture(texture);
}

void TieFighter::Movement(sf::RenderWindow &window, double elapsed){
    if(this->getGlobalBounds().left < 0){
//        this->setPosition(this->getGlobalBounds().width/2, this->getPosition().y);
        this->speed_x = -speed_x;
    }
    if(this->getGlobalBounds().left + this->getGlobalBounds().width >= window.getSize().x){
//        this->setPosition(window.getSize().x - this->getGlobalBounds().width/2, this->getPosition().y);
        this->speed_x = -speed_x;
    }

    this->move(speed_x*elapsed, speed_y*elapsed);
}

void TieFighter::LostHP(int x){
    this->hp -= x;
}

int TieFighter::GetHP(){
    return hp;
}
