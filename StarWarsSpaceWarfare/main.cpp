#include "button.h"
#include "normalshot.h"
#include "player.h"
#include "tiefighter.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

void Game(){
    // create the window
    // SOUND
    sf::SoundBuffer buffer_shot;
    if(!buffer_shot.loadFromFile("samples/x_wing_shot.wav")){
        std::cerr<<"blad ladowania x_wing_shot.wav"<<std::endl;
    }

    sf::Sound shot_right;
    shot_right.setBuffer(buffer_shot);
    shot_right.setVolume(10);

    sf::Sound shot_left;
    shot_left.setBuffer(buffer_shot);
    shot_left.setVolume(10);

    sf::RenderWindow window(sf::VideoMode(960, 540), "Star Wars - The Space warfare", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    // create some objects

    // PLAYER
    sf::Texture texture_x_wing;
    if(!texture_x_wing.loadFromFile("textures/x_wing.png")){
        std::cerr<<"Blad ladowania x_wing.png"<<std::endl;
    }
    sf::Texture texture_x_wing_power_up;
    if(!texture_x_wing_power_up.loadFromFile("textures/x_wing_power_up.png")){
        std::cerr<<"blad ladowania x_wing_power_up.png"<<std::endl;
    }
    sf::Texture texture_x_wing_destroyed;
    if(!texture_x_wing_destroyed.loadFromFile("textures/x_wing_destroyed.png")){
        std::cerr<<"blad ladowania x_wing.png"<<std::endl;
    }

    Player player(texture_x_wing);
    player.setOrigin(player.getGlobalBounds().width/2, player.getGlobalBounds().height/2);
    player.setPosition(window.getSize().x/2, window.getSize().y/2 + 200);
    player.setScale(0.1, 0.1);

    // OPPONENTS
    sf::Texture texture_tie_fighter;
    if(!texture_tie_fighter.loadFromFile("textures/tie_fighter.png")){
        std::cerr<<"blad ladowania texture_tie_fighter.png"<<std::endl;
    }

    std::vector<std::unique_ptr<Opponents>> opponents;
    for(int i=0; i<10; i++){
        auto temp = std::make_unique<TieFighter>(texture_tie_fighter);
        temp->setPosition(rand()%(window.getSize().x-50), 0);
        temp->setScale(0.12, 0.12);
        opponents.emplace_back(std::move(temp));
    }

    // BACKGROUND
    sf::Texture texture_background;
    if(!texture_background.loadFromFile("textures/background1.png")){
        std::cerr<<"blad ladowania background.png"<<std::endl;
    }
    texture_background.setRepeated(true);

    sf::Sprite background(texture_background);
    background.setTextureRect(sf::IntRect(0, 0, 10*window.getSize().x, 10*window.getSize().y));
//    background.setScale(0.5, 0.5);
    background.setPosition(window.getSize().x, window.getSize().y);
    background.setRotation(180);

    sf::Texture texture_normal_shot_green;
    if(!texture_normal_shot_green.loadFromFile("textures/shot_green.png")){
        std::cerr<<"blad ladowania shot_green.png"<<std::endl;
    }

    sf::Texture texture_normal_shot_red;
    if(!texture_normal_shot_red.loadFromFile("textures/shot_red.png")){
        std::cerr<<"blad ladowania shot_red.png"<<std::endl;
    }

    std::vector<std::unique_ptr<Bullet>> bullets;

    // CLOCKS
    sf::Clock clock;
    double elapsed;
    double elapsedPowerUp = 0;
    double elapsedShot = 0;

    enum{
        left_gun,
        right_gun
    };

    bool WhichGun = left_gun;

    // run the program as long as the window is open
    while(window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        elapsed = clock.restart().asSeconds();
        elapsedPowerUp += elapsed;
        elapsedShot += elapsed;

        while(window.pollEvent(event)) {
            // "close requested" event: we close the window
            if(event.type == sf::Event::Closed){
                window.close();
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
                if(elapsedPowerUp > 0.2){
                    player.TogglePowerUp(texture_x_wing_power_up, texture_x_wing);
                    elapsedPowerUp = 0;
                }
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            player.move(-player.GetSpeedX()*elapsed, 0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            player.move(player.GetSpeedX()*elapsed, 0);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            if(elapsedShot > 0.2){
                auto temp = std::make_unique<NormalShot>(texture_normal_shot_red);
                if(WhichGun == left_gun){
                    temp->ShootLeft(player);
                    shot_left.play();
                    WhichGun = right_gun;
                }
                else{
                    temp->ShootRight(player);
                    shot_right.play();
                    WhichGun = left_gun;
                }
                bullets.emplace_back(std::move(temp));
                elapsedShot = 0;
            }
        }

        // LOGIC
        player.BorderLimit(window);
        if(player.getPosition().y < 500){
            player.move(0, 100*elapsed);
        }

        background.move(0, 15*elapsed);

        for(auto it=bullets.begin(); it!=bullets.end();){
            if((*it)->getGlobalBounds().top + (*it)->getGlobalBounds().height < -100){
                NormalShot *normalShot = dynamic_cast<NormalShot*>(it->get());
                if(normalShot!=nullptr){
                    it = bullets.erase(it);
                }
                else{}
            }
            else{
                it++;
            }
        }

        for(auto it=bullets.begin(); it!=bullets.end(); it++){
            (*it)->Move(elapsed);
        }



        for(auto it=opponents.begin(); it!=opponents.end();){
            TieFighter *tiefighter = dynamic_cast<TieFighter*>(it->get());
            tiefighter->Movement(window, elapsed);
            if(tiefighter!=nullptr){
                for(auto itr=bullets.begin(); itr!=bullets.end();){
                    NormalShot *normalshot = dynamic_cast<NormalShot*>(itr->get());
                    if(normalshot!=nullptr){
                        if(normalshot->getGlobalBounds().intersects(tiefighter->getGlobalBounds())){
                            tiefighter->LostHP(25);
                            itr = bullets.erase(itr);
                            std::cout<<"BOOM"<<std::endl;
                        }
                        else{
                            itr++;
                        }
                    }
                    else{
                        itr++;
                    }
                }
                it++;
            }
            else{
                it++;
            }
        }

        for(auto it=opponents.begin(); it!=opponents.end();){
            TieFighter *tiefighter = dynamic_cast<TieFighter*>(it->get());
            if(tiefighter!=nullptr){
                tiefighter->Movement(window, elapsed);
                if(tiefighter->GetHP() <= 0){
                    it = opponents.erase(it);
                }
                else{
                    it++;
                }
            }
            else {
                it++;
            }
        }

        //std::cout<<1.f/elapsed<<std::endl;

        // clear the window with black color / background image
        //window.clear(sf::Color::Black);
        window.draw(background);

        // DRAW
        // draw everything here...
        for(auto &el: bullets){
            window.draw(*el);
        }

        for(auto &el: opponents){
            window.draw(*el);
        }

        window.draw(player);

        // end the current frame
        window.display();
    }
}
void MainMenu(){
    sf::SoundBuffer buffer;
    if(!buffer.loadFromFile("samples/mainmenutheme.wav")){
        std::cerr<<"blad ladowania mainmenutheme.wav"<<std::endl;
    }

    // create the window
    sf::RenderWindow window(sf::VideoMode(960, 540), "Star Wars - The Space warfare", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    sf::Texture texture_intro;
    texture_intro.loadFromFile("textures/intro1.jpg");
    texture_intro.setRepeated(false);

    sf::Sprite intro(texture_intro);

    sf::Sound theme;
    theme.setBuffer(buffer);
    theme.play();
    theme.setVolume(10); // zmienic na 10

    sf::Font font;
    if(!font.loadFromFile("fonts/Starjedi.ttf")){
        std::cerr<<"blad ladowania Starjedi.ttf"<<std::endl;
    }

    //Play button
    Button play;
    play.setFont(font);
    play.setFillColor(sf::Color::White);
    play.setOutlineColor(sf::Color::Black);
    play.setOutlineThickness(0.5);
    play.setString("play");
    play.setCharacterSize(50);
    play.setPosition(650, 300);

    //Options button
    Button options;
    options.setFont(font);
    options.setFillColor(sf::Color::White);
    options.setOutlineColor(sf::Color::Black);
    options.setOutlineThickness(0.5);
    options.setString("options");
    options.setCharacterSize(50);
    options.setPosition(650, 370);

    //About button
    Button about;
    about.setFont(font);
    about.setFillColor(sf::Color::White);
    about.setOutlineColor(sf::Color::Black);
    about.setOutlineThickness(0.5);
    about.setString("about");
    about.setCharacterSize(50);
    about.setPosition(650, 440);

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
        if((window.mapPixelToCoords(sf::Mouse::getPosition(window)).x < play.getPosition().x + play.getGlobalBounds().width)
                && (window.mapPixelToCoords(sf::Mouse::getPosition(window)).x > play.getPosition().x)
                && (window.mapPixelToCoords(sf::Mouse::getPosition(window)).y > play.getPosition().y)
                && (window.mapPixelToCoords(sf::Mouse::getPosition(window)).y < play.getPosition().y + play.getGlobalBounds().height)){
            play.setFillColor(sf::Color(241, 212, 0));
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                window.close();
                Game();
            }
        }
        else {
            play.setFillColor(sf::Color::White);
        }
        if((window.mapPixelToCoords(sf::Mouse::getPosition(window)).x < options.getPosition().x + options.getGlobalBounds().width)
                && (window.mapPixelToCoords(sf::Mouse::getPosition(window)).x > options.getPosition().x)
                && (window.mapPixelToCoords(sf::Mouse::getPosition(window)).y > options.getPosition().y)
                && (window.mapPixelToCoords(sf::Mouse::getPosition(window)).y < options.getPosition().y + options.getGlobalBounds().height)){
            options.setFillColor(sf::Color(241, 212, 0));
        }
        else {
            options.setFillColor(sf::Color::White);
        }
        if((window.mapPixelToCoords(sf::Mouse::getPosition(window)).x < about.getPosition().x + about.getGlobalBounds().width)
                && (window.mapPixelToCoords(sf::Mouse::getPosition(window)).x > about.getPosition().x)
                && (window.mapPixelToCoords(sf::Mouse::getPosition(window)).y > about.getPosition().y)
                && (window.mapPixelToCoords(sf::Mouse::getPosition(window)).y < about.getPosition().y + about.getGlobalBounds().height)){
            about.setFillColor(sf::Color(241, 212, 0));
        }
        else {
            about.setFillColor(sf::Color::White);
        }

        // clear the window with black color / background image
        //window.clear(sf::Color::Black);
        window.draw(intro);


        // DRAW
        // draw everything here...
        window.draw(play);
        window.draw(options);
        window.draw(about);



        // end the current frame
        window.display();
    }
}
void Options(){
    // create the window
    sf::RenderWindow window(sf::VideoMode(960, 540), "Star Wars - The Space warfare", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
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



        // DRAW
        // draw everything here...




        // end the current frame
        window.display();
    }
}

int main(){
    MainMenu();

    return 0;
}
