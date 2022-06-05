#pragma once
#include "SFML/Audio/Sound.hpp"

class Options : public sf::Sound
{
public:
    Options();
    void changeSoundLevel(float x);
private:
    float soundLevel;
};
