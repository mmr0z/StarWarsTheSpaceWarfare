#include "normalshot.h"

NormalShot::NormalShot(sf::Texture &texture)
{
    this->SetSpeed(0, 700);

    setTexture(texture);
}
