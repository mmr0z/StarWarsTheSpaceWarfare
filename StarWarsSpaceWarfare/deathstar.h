#pragma once
#include "opponents.h"

class DeathStar : public Opponents
{
public:
    DeathStar(sf::Texture &texture);
    void Bounce(sf::RenderWindow &window, double elapsed);
    void HP();
    void HPdraw();
    void SetHP(int x);
};
