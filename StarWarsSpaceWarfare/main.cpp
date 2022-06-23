#include "button.h"
#include "normalshot.h"
#include "player.h"
#include "protonbomb.h"
#include "tiefighter.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>

void About(){
    sf::Font font;
    if(!font.loadFromFile("fonts/Starjedi.ttf")){
        std::cerr<<"blad ladowania Starjedi.ttf"<<std::endl;
    }

    sf::RenderWindow window(sf::VideoMode(420, 350), "Star Wars - The Space warfare", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    Button author;
    author.setFont(font);
    author.setFillColor(sf::Color::Black);
    author.setOutlineColor(sf::Color::White);
    author.setOutlineThickness(0.8);
    author.setString("author: maciej mroz \nindex: 151241 \npolitechnika poznanska \nair 2022, 2nd semester \n-------------------------------------------- \na - left, d - right \nspace - shoot, p - shop, \nenter - pause");
    author.setCharacterSize(25);
    author.setPosition(10, 10);

    while(window.isOpen()) {

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        while(window.pollEvent(event)) {
            // "close requested" event: we close the window
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        window.clear(sf::Color::Black);

        window.draw(author);

        window.display();
    }
}
void Shop(Player &player){
    sf::Font font;
    if(!font.loadFromFile("fonts/Starjedi.ttf")){
        std::cerr<<"blad ladowania Starjedi.ttf"<<std::endl;
    }

    sf::RenderWindow window(sf::VideoMode(420, 340), "Star Wars - The Space warfare", sf::Style::None);
    window.setFramerateLimit(60);

    sf::Texture texture_proton_bomb;
    if(!texture_proton_bomb.loadFromFile("textures/proton_bomb.png")){
        std::cerr<<"blad ladowania proton_bomb.png"<<std::endl;
    }

    const sf::Texture *pTexture_proton = &texture_proton_bomb;
    sf::RectangleShape proton_image;
    proton_image.setTexture(pTexture_proton);
    proton_image.setRotation(270);
    proton_image.setPosition(70, 195);
    proton_image.setSize(sf::Vector2f(30, 114));

    Button close;
    close.setFont(font);
    close.setFillColor(sf::Color::Red);
    close.setOutlineColor(sf::Color::White);
    close.setOutlineThickness(0.8);
    close.setString("x");
    close.setCharacterSize(50);
    close.setPosition(370, 0);

    Button points;
    points.setFont(font);
    points.setFillColor(sf::Color::Black);
    points.setOutlineColor(sf::Color::White);
    points.setOutlineThickness(0.8);
    points.setString(std::to_string(player.GetPoints()));
    points.setCharacterSize(50);
    points.setPosition(270, 45);

    Button points_text;
    points_text.setFont(font);
    points_text.setFillColor(sf::Color::Black);
    points_text.setOutlineColor(sf::Color::White);
    points_text.setOutlineThickness(0.8);
    points_text.setString("points:");
    points_text.setCharacterSize(50);
    points_text.setPosition(50, 45);

    Button buy_proton_bomb;
    buy_proton_bomb.setFont(font);
    buy_proton_bomb.setFillColor(sf::Color::Black);
    buy_proton_bomb.setOutlineColor(sf::Color::White);
    buy_proton_bomb.setOutlineThickness(0.8);
    buy_proton_bomb.setString("buy");
    buy_proton_bomb.setCharacterSize(50);
    buy_proton_bomb.setPosition(230, 145);

    Button how_much_bombs;
    how_much_bombs.setFont(font);
    how_much_bombs.setFillColor(sf::Color::Black);
    how_much_bombs.setOutlineColor(sf::Color::White);
    how_much_bombs.setOutlineThickness(0.8);
    how_much_bombs.setString(std::to_string(player.GetProtonBomb()));
    how_much_bombs.setCharacterSize(50);
    how_much_bombs.setPosition(270, 245);

    Button bombs_text;
    bombs_text.setFont(font);
    bombs_text.setFillColor(sf::Color::Black);
    bombs_text.setOutlineColor(sf::Color::White);
    bombs_text.setOutlineThickness(0.8);
    bombs_text.setString("bombs:");
    bombs_text.setCharacterSize(50);
    bombs_text.setPosition(50, 245);

    while(window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        while(window.pollEvent(event)) {
            // "close requested" event: we close the window
            if(event.type == sf::Event::Closed){
                window.close();
            }
            if((window.mapPixelToCoords(sf::Mouse::getPosition(window)).x < buy_proton_bomb.getPosition().x + buy_proton_bomb.getGlobalBounds().width)
                    && (window.mapPixelToCoords(sf::Mouse::getPosition(window)).x > buy_proton_bomb.getPosition().x)
                    && (window.mapPixelToCoords(sf::Mouse::getPosition(window)).y > buy_proton_bomb.getPosition().y)
                    && (window.mapPixelToCoords(sf::Mouse::getPosition(window)).y < buy_proton_bomb.getPosition().y + buy_proton_bomb.getGlobalBounds().height)){
                buy_proton_bomb.setFillColor(sf::Color(241, 212, 0));
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    if(player.GetPoints() > 2){
                        player.AddPoints(-3);
                        player.AddProtonBomb(1);
                    }
                }
            }
            else{
                buy_proton_bomb.setFillColor(sf::Color::Black);
            }
            if((window.mapPixelToCoords(sf::Mouse::getPosition(window)).x < close.getPosition().x + close.getGlobalBounds().width)
                    && (window.mapPixelToCoords(sf::Mouse::getPosition(window)).x > close.getPosition().x)
                    && (window.mapPixelToCoords(sf::Mouse::getPosition(window)).y > close.getPosition().y)
                    && (window.mapPixelToCoords(sf::Mouse::getPosition(window)).y < close.getPosition().y + close.getGlobalBounds().height)){
                close.setFillColor(sf::Color(241, 212, 0));
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    window.close();
                }
            }
            else{
                close.setFillColor(sf::Color::Red);
            }
        }

        // LOGIC
        window.clear(sf::Color::Black);

        points.setString(std::to_string(player.GetPoints()));
        how_much_bombs.setString(std::to_string(player.GetProtonBomb()));

        // DRAW
        window.draw(buy_proton_bomb);
        window.draw(points);
        window.draw(points_text);
        window.draw(how_much_bombs);
        window.draw(bombs_text);
        window.draw(close);
        window.draw(proton_image);

        window.display();
    }
}
void Game(){
    // create the window
    // SOUND
    sf::SoundBuffer buffer_shot;
    if(!buffer_shot.loadFromFile("samples/x_wing_shot.wav")){
        std::cerr<<"blad ladowania x_wing_shot.wav"<<std::endl;
    }

    sf::SoundBuffer buffer_death_star_shot;
    if(!buffer_death_star_shot.loadFromFile("samples/death_star_shot.wav")){
        std::cerr<<"blad ladowania death_star_shot.wav"<<std::endl;
    }

    sf::SoundBuffer buffer_proton_bomb_explosion;
    if(!buffer_proton_bomb_explosion.loadFromFile("samples/proton_bomb_explosion.wav")){
        std::cerr<<"blad ladowania proton_bomb_explosion.wav"<<std::endl;
    }

    sf::Sound proton_explosion;
    proton_explosion.setBuffer(buffer_proton_bomb_explosion);
    proton_explosion.setVolume(5);

    sf::Sound shot_right;
    shot_right.setBuffer(buffer_shot);
    shot_right.setVolume(10);

    sf::Sound shot_left;
    shot_left.setBuffer(buffer_shot);
    shot_left.setVolume(10);

    sf::Sound death_star_shot;
    death_star_shot.setBuffer(buffer_death_star_shot);
    death_star_shot.setVolume(10);

    sf::Font font;
    if(!font.loadFromFile("fonts/Starjedi.ttf")){
        std::cerr<<"blad ladowania Starjedi.ttf"<<std::endl;
    }

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
        std::cerr<<"blad ladowania tie_fighter.png"<<std::endl;
    }

    sf::Texture texture_death_star;
    if(!texture_death_star.loadFromFile("textures/death_star.png")){
        std::cerr<<"blad ladowania death_star.png"<<std::endl;
    }

    DeathStar deathstar(texture_death_star);

    std::vector<std::unique_ptr<Opponents>> opponents;

    Button pause_text;
    pause_text.setFont(font);
    pause_text.setFillColor(sf::Color::Black);
    pause_text.setOutlineColor(sf::Color::White);
    pause_text.setOutlineThickness(0.8);
    pause_text.setString("paused! press enter");
    pause_text.setCharacterSize(50);
    pause_text.setPosition(170, 245);

    Button points_text;
    points_text.setFont(font);
    points_text.setFillColor(sf::Color::Black);
    points_text.setOutlineColor(sf::Color::White);
    points_text.setOutlineThickness(0.8);
    points_text.setString(std::to_string(player.GetPoints()));
    points_text.setCharacterSize(25);
    points_text.setPosition(10, 10);

    Button HP_text;
    HP_text.setFont(font);
    HP_text.setFillColor(sf::Color::Black);
    HP_text.setOutlineColor(sf::Color::White);
    HP_text.setOutlineThickness(0.8);
    HP_text.setString(std::to_string(player.GetHP()));
    HP_text.setCharacterSize(25);
    HP_text.setPosition(900, 10);

    Button HP;
    HP.setFont(font);
    HP.setFillColor(sf::Color::Black);
    HP.setOutlineColor(sf::Color::White);
    HP.setOutlineThickness(0.8);
    HP.setString("hp:");
    HP.setCharacterSize(25);
    HP.setPosition(820, 10);

    Button proton_text;
    proton_text.setFont(font);
    proton_text.setFillColor(sf::Color::Black);
    proton_text.setOutlineColor(sf::Color::White);
    proton_text.setOutlineThickness(0.8);
    proton_text.setString(std::to_string(player.GetProtonBomb()));
    proton_text.setCharacterSize(25);
    proton_text.setPosition(100, 495);

    // BACKGROUND
    sf::Texture texture_background;
    if(!texture_background.loadFromFile("textures/background1.png")){
        std::cerr<<"blad ladowania background.png"<<std::endl;
    }
    texture_background.setRepeated(true);

    sf::Sprite background(texture_background);
    background.setTextureRect(sf::IntRect(0, 0, window.getSize().x, 50*window.getSize().y));
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

    sf::Texture texture_proton_bomb;
    if(!texture_proton_bomb.loadFromFile("textures/proton_bomb.png")){
        std::cerr<<"blad ladowania proton_bomb.png"<<std::endl;
    }

    const sf::Texture *pTexture_proton = &texture_proton_bomb;
    sf::RectangleShape proton_image;
    proton_image.setTexture(pTexture_proton);
    proton_image.setRotation(270);
    proton_image.setPosition(20, 520);
    proton_image.setSize(sf::Vector2f(30, 114));
    proton_image.setScale(0.5, 0.50);

    std::vector<std::unique_ptr<Bullet>> bullets;
    std::vector<std::unique_ptr<Bullet>> bulletsDeathStar;

    // CLOCKS
    sf::Clock clock;
    sf::Clock timer;
    double elapsed = 0;
    double elapsedShot = 0;
    double elapsedShotProtonBomb = 0;
    double elapsedDeathStarShot = 0;
    double elapsedInterval = 0;
    double tempDSS = 0;
    double tempI = 0;

    enum{
        left_gun,
        right_gun
    };

    bool WhichGun = left_gun;
    bool pause = false;

    // run the program as long as the window is open
    while(window.isOpen()) {

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        elapsed = clock.restart().asSeconds();
        elapsedShot += elapsed;
        elapsedShotProtonBomb += elapsed;
        elapsedDeathStarShot += elapsed;
        elapsedInterval += elapsed;


        while(window.pollEvent(event)) {
            // "close requested" event: we close the window
            if(event.type == sf::Event::Closed){
                window.close();
            }

            if(event.type == sf::Event::KeyReleased){
                if(event.key.code == sf::Keyboard::P){
                    pause = true;
                    Shop(player);
                }
            }
            if(event.type == sf::Event::KeyReleased){
                if(event.key.code == sf::Keyboard::Enter){
                    pause=!pause;
                    elapsedDeathStarShot = tempDSS;
                    elapsedInterval = tempI;
                }
            }
        }

        points_text.setString(std::to_string(player.GetPoints()));
        HP_text.setString(std::to_string(player.GetHP()));
        proton_text.setString(std::to_string(player.GetProtonBomb()));

        //
        if(!pause){
            tempDSS = elapsedDeathStarShot;
            tempI = elapsedInterval;

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                player.move(-player.GetSpeedX()*elapsed, 0);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                player.move(player.GetSpeedX()*elapsed, 0);
            }

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                if(elapsedShotProtonBomb > 1){
                    if(player.GetProtonBomb() > 0){
                        auto temp = std::make_unique<ProtonBomb>(texture_proton_bomb, player);
                        temp->ShootToTarget(player, window, elapsed);
                        temp->setScale(0.4, 0.4);

                        bullets.emplace_back(std::move(temp));
                        player.AddProtonBomb(-1);
                        elapsedShotProtonBomb = 0;
                    }
                }
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

            if(elapsedInterval > 2){
                if(elapsedDeathStarShot > 0.005){
                    auto temp = std::make_unique<NormalShot>(texture_normal_shot_green);
                    temp->SetSpeed(0, 500);
                    temp->ShootLaser(deathstar);
                    bulletsDeathStar.emplace_back(std::move(temp));
                    elapsedDeathStarShot = 0;
                    if(elapsedInterval > 2.5){
                        elapsedInterval = 0;
                        death_star_shot.play();
                    }
                }
            }

            // LOGIC
            player.BorderLimit(window);

            if(player.GetHP() <= 100){
                player.setTexture(texture_x_wing_destroyed);
            }

            if(player.getPosition().y < 500){
                player.move(0, 100*elapsed);
            }

            background.move(0, 15*elapsed);

            for(auto it=bullets.begin(); it!=bullets.end();){
                if((*it)->getGlobalBounds().top + (*it)->getGlobalBounds().height < -20){
                    NormalShot *normalShot = dynamic_cast<NormalShot*>(it->get());
                    ProtonBomb *protonBomb = dynamic_cast<ProtonBomb*>(it->get());
                    if(normalShot!=nullptr){
                        it = bullets.erase(it);
                    }
                    else if(protonBomb!=nullptr){
                        it = bullets.erase(it);
                    }
                    else{}
                }
                else{
                    it++;
                }
            }

            for(auto it=bulletsDeathStar.begin(); it!=bulletsDeathStar.end();){
                if((*it)->getGlobalBounds().top > 600){
                    NormalShot *normalShot = dynamic_cast<NormalShot*>(it->get());
                    if(normalShot!=nullptr){
                        it = bulletsDeathStar.erase(it);
                    }
                    else{

                    }
                }
                else{
                    it++;
                }
            }

            for(auto it=bulletsDeathStar.begin(); it!=bulletsDeathStar.end();){
                if((*it)->getGlobalBounds().intersects(player.getGlobalBounds())){
                    NormalShot *normalShot = dynamic_cast<NormalShot*>(it->get());
                    if(normalShot!=nullptr){
                        it = bulletsDeathStar.erase(it);
                        player.AddHP(-1);
                    }
                    else{

                    }
                }
                else{
                    it++;
                }
            }

            for(auto &el: bulletsDeathStar){
                el->Shoot(elapsed);
            }

            for(auto it=bullets.begin(); it!=bullets.end(); it++){
                NormalShot *normalShot = dynamic_cast<NormalShot*>(it->get());
                ProtonBomb *protonBomb = dynamic_cast<ProtonBomb*>(it->get());
                if(normalShot!=nullptr){
                    normalShot->Shoot(elapsed);
                }
                else if(protonBomb!=nullptr){
                    protonBomb->ShootToTarget(player, window, elapsed);
                }
            }

            for(auto it=opponents.begin(); it!=opponents.end();){
                TieFighter *tiefighter = dynamic_cast<TieFighter*>(it->get());
                tiefighter->Movement(window, elapsed);
                if(tiefighter!=nullptr){
                    for(auto itr=bullets.begin(); itr!=bullets.end();){
                        NormalShot *normalshot = dynamic_cast<NormalShot*>(itr->get());
                        ProtonBomb *protonbomb = dynamic_cast<ProtonBomb*>(itr->get());
                        if(normalshot!=nullptr){
                            if(normalshot->getGlobalBounds().intersects(tiefighter->getGlobalBounds())){
                                tiefighter->LostHP(20+rand()%10);
                                itr = bullets.erase(itr);
                            }
                            else if(normalshot->getGlobalBounds().intersects(deathstar.getGlobalBounds())){
                                deathstar.LostHP(3);
                                itr = bullets.erase(itr);
                            }
                            else{
                                itr++;
                            }
                        }
                        else if(protonbomb!=nullptr){
                            if(protonbomb->getGlobalBounds().intersects(tiefighter->getGlobalBounds())){
                                tiefighter->LostHP(50);
                                proton_explosion.play();
                                itr = bullets.erase(itr);
                            }
                            else if(protonbomb->getGlobalBounds().intersects(deathstar.getGlobalBounds())){
                                deathstar.LostHP(30);
                                proton_explosion.play();
                                itr = bullets.erase(itr);
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
                        player.AddPoints(1);
                        it = opponents.erase(it);
                    }
                    else if(tiefighter->getPosition().y > window.getSize().y){
                        it = opponents.erase(it);
                        player.AddHP(-10);
                    }
                    else{
                        it++;
                    }
                }
                else {
                    it++;
                }
            }
            deathstar.Bounce(window, elapsed);
        }

        if(opponents.empty()){
            for(int i=0; i<10; i++){
                auto temp = std::make_unique<TieFighter>(texture_tie_fighter);
                temp->setPosition(10 + rand()%(window.getSize().x-50), -200);
                temp->setScale(0.12, 0.12);
                opponents.emplace_back(std::move(temp));
            }
        }

        if(deathstar.GetHP() <= 0){
            deathstar.SetHP(0);
            pause_text.setString("you win!");
            pause_text.setPosition(380, 245);
            pause = true;
        }

        if(player.GetHP() <= 0){
            pause = true;
            pause_text.setString("you lost!");
            pause_text.setPosition(370, 245);
        }

        // clear the window with black color / background image
        //window.clear(sf::Color::Black);
        window.draw(background);

        // DRAW
        // draw everything here...

        if(deathstar.GetHP() > 0){
            window.draw(deathstar);
        }

        deathstar.HPdraw();
        window.draw(deathstar.hp_bar);
        window.draw(player);

        for(auto &el: bulletsDeathStar){
            window.draw(*el);
        }
        for(auto &el: opponents){
            window.draw(*el);
        }

        for(auto &el: bullets){
            window.draw(*el);
        }

        for(auto &el: opponents){
            el->HPdraw();
            window.draw(el->hp_bar);
        }

        if(pause){
            window.draw(pause_text);
        }

        window.draw(points_text);
        window.draw(HP_text);
        window.draw(proton_image);
        window.draw(proton_text);
        window.draw(HP);

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
    texture_intro.loadFromFile("textures/intro.png");
    texture_intro.setRepeated(false);

    sf::Sprite intro(texture_intro);

    sf::Sound theme;
    theme.setBuffer(buffer);
    theme.play();
    theme.setVolume(5);

    sf::Font font;
    if(!font.loadFromFile("fonts/Starjedi.ttf")){
        std::cerr<<"blad ladowania Starjedi.ttf"<<std::endl;
    }

    //LOGO
    Button logo_star_wars;
    logo_star_wars.setFont(font);
    logo_star_wars.setFillColor(sf::Color::Black);
    logo_star_wars.setOutlineColor(sf::Color::White);
    logo_star_wars.setOutlineThickness(0.8);
    logo_star_wars.setString("star wars");
    logo_star_wars.setCharacterSize(70);
    logo_star_wars.setPosition(80, 300);

    Button logo_the_space;
    logo_the_space.setFont(font);
    logo_the_space.setFillColor(sf::Color(241, 212, 0));
    logo_the_space.setOutlineColor(sf::Color::Black);
    logo_the_space.setOutlineThickness(0.8);
    logo_the_space.setString("the space warfare");
    logo_the_space.setCharacterSize(37);
    logo_the_space.setPosition(80, 370);

    //Play button
    Button play;
    play.setFont(font);
    play.setFillColor(sf::Color::White);
    play.setOutlineColor(sf::Color::Black);
    play.setOutlineThickness(0.5);
    play.setString("play");
    play.setCharacterSize(50);
    play.setPosition(650, 300);

    //About button
    Button about;
    about.setFont(font);
    about.setFillColor(sf::Color::White);
    about.setOutlineColor(sf::Color::Black);
    about.setOutlineThickness(0.5);
    about.setString("about");
    about.setCharacterSize(50);
    about.setPosition(650, 370);

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

        if((window.mapPixelToCoords(sf::Mouse::getPosition(window)).x < about.getPosition().x + about.getGlobalBounds().width)
                && (window.mapPixelToCoords(sf::Mouse::getPosition(window)).x > about.getPosition().x)
                && (window.mapPixelToCoords(sf::Mouse::getPosition(window)).y > about.getPosition().y)
                && (window.mapPixelToCoords(sf::Mouse::getPosition(window)).y < about.getPosition().y + about.getGlobalBounds().height)){
            about.setFillColor(sf::Color(241, 212, 0));
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                About();
            }
        }
        else {
            about.setFillColor(sf::Color::White);
        }

        // clear the window with black color / background image
        //window.clear(sf::Color::Black);
        window.draw(intro);

        // DRAW
        // draw everything here...
        window.draw(logo_star_wars);
        window.draw(logo_the_space);
        window.draw(play);
        window.draw(about);

        // end the current frame
        window.display();
    }
}

int main(){
    MainMenu();
    return 0;
}
