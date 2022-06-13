#pragma once
#include "bullet.h"
#include "opponents.h"

class ProtonBomb : public Bullet
{
public:
    ProtonBomb(sf::Texture &texture, Player &player);
    void ShootToTarget(Player &player, sf::RenderWindow &window, double elapsed);
};
