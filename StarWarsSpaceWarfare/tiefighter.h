#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "opponents.h"

class TieFighter : public Opponents
{
public:
    TieFighter(sf::Texture &texture);

    void Movement(sf::RenderWindow &window, double elapsed);
    void LostHP(int x);
    void HP();
    int GetHP();
    void HPdraw();
};
