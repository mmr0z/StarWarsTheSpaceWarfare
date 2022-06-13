#include "opponents.h"

Opponents::Opponents()
{

}

int Opponents::GetHP(){
    return hp;
}

void Opponents::HPdraw(){
    this->hp_bar.setPosition(this->getPosition().x + 7, this->getPosition().y - 2);
    this->hp_bar.setSize(sf::Vector2f(this->GetHP(), 6));
}
