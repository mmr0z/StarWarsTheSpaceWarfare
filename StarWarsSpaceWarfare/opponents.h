#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Opponents : public sf::Sprite
{
public:
    Opponents();
    void Movement(sf::RenderWindow &window, double elapsed);
protected:
    int hp;
    int points;
    double speed_x;
    double speed_y;
};
