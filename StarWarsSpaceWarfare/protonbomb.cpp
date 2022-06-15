#include "protonbomb.h"
#include <cmath>

ProtonBomb::ProtonBomb(sf::Texture &texture, Player &player)
{
    this->setTexture(texture);
    setPosition(player.getPosition().x - 8, player.getPosition().y);
}

void ProtonBomb::ShootToTarget(Player &player, sf::RenderWindow &window, double elapsed){
    this->speed_x = 500;
    this->speed_y = -300;

    sf::Vector2f pos_m = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    sf::Vector2f pos_s = player.getPosition();
    sf::Vector2f diff = pos_m - pos_s;
    double normalizer = sqrt(pow(diff.x, 2) + pow(diff.y, 2));
    if((std::abs(diff.x)>2) && (std::abs(diff.y)>2)){
        this->move(((diff.x)*speed_x/normalizer)*elapsed, (diff.y*speed_y/normalizer)*elapsed);
    }
}
