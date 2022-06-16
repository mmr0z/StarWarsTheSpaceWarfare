#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Opponents : public sf::Sprite
{
public:
    Opponents();
    void Movement(sf::RenderWindow &window, double elapsed);
    void HP();
    sf::RectangleShape hp_bar;
    int GetHP();
    virtual void LostHP(int x);
    void HPdraw();
protected:
    int hp;
    int points;
    double speed_x;
    double speed_y;
};
