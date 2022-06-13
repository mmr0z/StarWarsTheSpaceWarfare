#include "tiefighter.h"

TieFighter::TieFighter(sf::Texture &texture)
{
    this->speed_x = rand()%100 - 50;
    this->speed_y = rand()%15 + 10;

    this->hp = 50;

    setTexture(texture);
    HP();
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

void TieFighter::HP(){
    hp_bar.setSize(sf::Vector2f(GetHP(), 6));
    hp_bar.setFillColor(sf::Color::Red);
    hp_bar.setOutlineColor(sf::Color(153, 153, 153));
    hp_bar.setOutlineThickness(1);
}

void TieFighter::HPdraw(){
    this->hp_bar.setPosition(this->getPosition().x + 7, this->getPosition().y - 2);
    this->hp_bar.setSize(sf::Vector2f(this->GetHP(),6));
};

void TieFighter::LostHP(int x){
    this->hp -= x;
}

int TieFighter::GetHP(){
    return hp;
}
