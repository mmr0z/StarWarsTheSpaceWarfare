#include "deathstar.h"

DeathStar::DeathStar(sf::Texture &texture)
{
    this->setPosition(rand()%700 + 130, 15);

    setTexture(texture);
    this->speed_x = 100;
    this->setScale(0.5, 0.5);

    this->hp = 500;
    HP();
}

void DeathStar::Bounce(sf::RenderWindow &window, double elapsed){
    if(this->getGlobalBounds().left + this->getGlobalBounds().width/2 >= window.getSize().x){
        this->speed_x = -speed_x;
    }

    if(this->getGlobalBounds().left < 0){
        this->setPosition(0, this->getPosition().y);
        this->speed_x = -speed_x;
    }

    this->move(speed_x*elapsed, 0);
}

void DeathStar::HP(){
    hp_bar.setFillColor(sf::Color::Red);
    hp_bar.setOutlineColor(sf::Color(153, 153, 153));
    hp_bar.setOutlineThickness(1);
}

void DeathStar::HPdraw(){
    this->hp_bar.setPosition(this->getPosition().x, this->getPosition().y - 2);
    this->hp_bar.setSize(sf::Vector2f((float) this->GetHP()/3.15, 6));
}

void DeathStar::SetHP(int x){
    this->hp = x;
}
