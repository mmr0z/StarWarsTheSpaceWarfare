#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Bullet : public sf::Sprite
{
public:
    Bullet();

    //virtual void Shoot();
    void SetSpeed(double sx, double sy);

protected:
    double speed_x;
    double speed_y;

};
