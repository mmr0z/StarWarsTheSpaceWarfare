#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "bullet.h"

class NormalShot : public Bullet
{
public:
    NormalShot(sf::Texture &texture);
};

