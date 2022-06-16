#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "bullet.h"
#include "player.h"

class NormalShot : public Bullet
{
public:
    NormalShot(sf::Texture &texture);
    void ShootLeft(Player &player);
    void ShootRight(Player &player);
    void ShootLaser(DeathStar &deathstar);
};

