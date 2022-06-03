#include "player.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

void Game(){
    // create the window
    sf::RenderWindow window(sf::VideoMode(960, 540), "Star Wars - The Space warfare");
    window.setFramerateLimit(60);

    // create some objects

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///
    // PLAYER
    sf::Texture texture_x_wing;
    if(!texture_x_wing.loadFromFile("C:/Users/macie/Desktop/PSIO/Star Wars - Space Warfare/StarWarsSpaceWarfare/StarWarsSpaceWarfare/textures/x_wing.png")){
        std::cerr<<"Blad ladowania x_wing.png"<<std::endl;
    }
    sf::Texture texture_x_wing_power_up;
    if(!texture_x_wing_power_up.loadFromFile("C:/Users/macie/Desktop/PSIO/Star Wars - Space Warfare/StarWarsSpaceWarfare/StarWarsSpaceWarfare/textures/x_wing_power_up.png")){
        std::cerr<<"blad ladowania x_wing_power_up.png"<<std::endl;
    }
    sf::Texture texture_x_wing_destroyed;
    if(!texture_x_wing_destroyed.loadFromFile("C:/Users/macie/Desktop/PSIO/Star Wars - Space Warfare/StarWarsSpaceWarfare/StarWarsSpaceWarfare/textures/x_wing_destroyed.png")){
        std::cerr<<"blad ladowania x_wing.png"<<std::endl;
    }

    Player player(texture_x_wing);
    player.setOrigin(player.getGlobalBounds().width/2, player.getGlobalBounds().height/2);
    player.setPosition(window.getSize().x/2, window.getSize().y/2);
    player.setScale(0.1, 0.1);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///
    // BACKGROUND
    sf::Texture texture_background;
    if(!texture_background.loadFromFile("C:/Users/macie/Desktop/PSIO/Star Wars - Space Warfare/StarWarsSpaceWarfare/StarWarsSpaceWarfare/textures/background.png")){
        std::cerr<<"blad ladowania background.png"<<std::endl;
    }
    texture_background.setRepeated(true);

    sf::Sprite background(texture_background);
    background.setTextureRect(sf::IntRect(0, 0, 1000, 1000));

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///
    // CLOCKS
    sf::Clock clock;

    // run the program as long as the window is open
    while(window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        double elapsed = clock.restart().asSeconds();

        while(window.pollEvent(event)) {
            // "close requested" event: we close the window
            if(event.type == sf::Event::Closed){
                window.close();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                player.move(-player.GetSpeedX()*elapsed, 0);
//                player.ChangeTexture(texture_x_wing_power_up);
//                std::cout<<"moving left"<<std::endl;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                player.move(player.GetSpeedX()*elapsed, 0);
//                std::cout<<"moving right"<<std::endl;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                player.ChangeTexture(texture_x_wing_power_up);
            }
        }

        // LOGIC
        player.BorderLimit(window);
//        std::cout<<1.f/elapsed<<std::endl;

        // clear the window with black color / background image
        //window.clear(sf::Color::Black);
        window.draw(background);

        // DRAW
        // draw everything here...
        window.draw(player);

        // end the current frame
        window.display();
    }
}

void MainMenu(){
    // create the window
    sf::RenderWindow window(sf::VideoMode(960, 540), "Star Wars - The Space warfare");
    window.setFramerateLimit(60);

    sf::Texture texture_intro;
    texture_intro.loadFromFile("C:/Users/macie/Desktop/PSIO/Star Wars - Space Warfare/StarWarsSpaceWarfare/StarWarsSpaceWarfare/textures/intro1.jpg");
    texture_intro.setRepeated(false);

    sf::Sprite intro(texture_intro);

    sf::SoundBuffer buffer;
    if(!buffer.loadFromFile("C:/Users/macie/Desktop/PSIO/Star Wars - Space Warfare/StarWarsSpaceWarfare/StarWarsSpaceWarfare/samples/mainmenutheme.wav")){
        std::cerr<<"blad ladowania mainmenutheme.wav"<<std::endl;
    }

    sf::Sound theme;
    theme.setBuffer(buffer);
    theme.play();
    theme.setVolume(10);

    while(window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        while(window.pollEvent(event)) {
            // "close requested" event: we close the window
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

        // LOGIC

        // clear the window with black color / background image
        //window.clear(sf::Color::Black);
        window.draw(intro);


        // DRAW
        // draw everything here...

        // end the current frame
        window.display();
    }
}

int main(){
    MainMenu();
    Game();

    return 0;
}
