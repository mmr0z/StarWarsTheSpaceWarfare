#include "player.h"
#include "normalshot.h"
#include <iostream>

Player::Player(sf::Texture &texture){
    setTexture(texture);

    this->SetSpeed(300, 300); /////////
}

void Player::SetSpeed(double sx, double sy){
    this->speed_x = sx;
    this->speed_y = sy;
}

void Player::BorderLimit(sf::RenderWindow &window){
    if(this->getGlobalBounds().left < 0){
        this->setPosition(this->getGlobalBounds().width/2, this->getPosition().y);
    }
    if(this->getGlobalBounds().left + this->getGlobalBounds().width > window.getSize().x){
        this->setPosition(window.getSize().x - this->getGlobalBounds().width/2, this->getPosition().y);
    }
}

void Player::ChangeTexture(sf::Texture &texture){
    this->setTexture(texture);
}

void Player::TogglePowerUp(sf::Texture &texture_power_up, sf::Texture &texture){
    power_up = !power_up;
    if(power_up){
        setTexture(texture_power_up);
    }
    else {
        setTexture(texture);
    }
}

int Player::GetLives(){
    return lives;
}

int Player::GetPoints(){
    return points;
}

double Player::GetSpeedX(){
    return speed_x;
}

double Player::GetSpeedY(){
    return speed_y;
}
