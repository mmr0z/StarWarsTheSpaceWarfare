#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Player : public sf::Sprite
{
public:
    Player(sf::Texture &texture);

    void SetSpeed(double sx, double sy);
    void BorderLimit(sf::RenderWindow &window);
    void ChangeTexture(sf::Texture &texture);
    void TogglePowerUp(sf::Texture &texture_power_up, sf::Texture &texture);

    int GetLives();
    int GetPoints();
    double GetSpeedX();
    double GetSpeedY();

protected:
    int lives;
    int points;
    double speed_x;
    double speed_y;
    bool power_up = false;
};
