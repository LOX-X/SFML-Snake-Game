#include "Game.h"
#include <iostream>
#include <vector>
#include "Snake.h"
#include "Text.h"
#include "Trackbar.h"


Game::Game(int width, int height) {
    this->window = new sf::RenderWindow(sf::VideoMode(width, height), "Snake", sf::Style::Close);//sf::Style::Close window not resizable
    this->width = width;
    this->height = height;
    //buttons positions, text, color,
    btnStart = new Button(sf::Vector2f(480, 710), "Start", sf::Color(153, 180, 209));
    btnStop = new Button(sf::Vector2f(480, 750), "Stop", sf::Color(238, 128, 128));
    btnClose = new Button(sf::Vector2f(690, 780), "Close", sf::Color(165, 42, 42));
    player = new Snake();
    allplayer = &player->getplayer();//get the player array
    food = new Food();
    scoretext = new Text(sf::Vector2f(20, 720));
    diedtext = new Text(sf::Vector2f(width /2, height /2));
    wintext = new Text(sf::Vector2f(width /2, height/ 2));
    trackbar = new Trackbar(sf::Vector2f(20, 770));
    this->window->setFramerateLimit(60);// fps
    Update();
}
    

void Game::Render() {
    scoretext->text.setString("Score: " + std::to_string(score));
    this->window->clear(sf::Color(109, 109, 109));
    PlayArea(*window);
    player->draw(*window);
    window->draw(food->getShape());
    btnStart->draw(*window);
    btnStop->draw(*window);
    btnClose->draw(*window);
    trackbar->draw(*window);
    scoretext->draw(*window);
    diedtext->draw(*window);
    wintext->draw(*window);
    this->window->display();
}

void Game::PlayArea(sf::RenderWindow& window) {
    sf::RectangleShape background(sf::Vector2f(780, 680));
    background.setPosition(sf::Vector2f(20, 20));
    background.setFillColor(sf::Color(255, 255, 225));
    window.draw(background);
}


void Game::Update() {
    sf::Clock clock;
    
    dir = RIGHT;//defult move on start
    food->spawn(300,300);// defult food spawn
    while (this->window->isOpen())
    {
        float speed = trackbar->getValue();
        
        sf::Event event;
        while (this->window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) this->window->close();
        }
        
        
        if (pause) {
            // movement
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                dir = RIGHT;

            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                dir = LEFT;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                dir = UP;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                dir = DOWN;
            }
            sf::Time time = clock.getElapsedTime();
            if (time.asMilliseconds() >= speed) {
                player->Move(dir);
                clock.restart();
            }
            
        }
        else {
            trackbar->handleEvent(event);
        }  

        // get mouse position
        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*window));
        // buttons on click
        if (btnStart->isClicked(mousePos, sf::Color(0, 120, 215))) {
            pause = true;
            btnStart->shape.setFillColor(sf::Color(232, 250, 129));
            btnStop->shape.setFillColor(sf::Color(238, 128, 128));

            if (gameEnd) {
                gameEnd = false;
                restart();
            }
        }
        if (btnStop->isClicked(mousePos, sf::Color::Red)) {
            pause = false;
            btnStop->shape.setFillColor(sf::Color(232, 250, 129));
            btnStart->shape.setFillColor(sf::Color(153, 180, 209));
        }
        if (btnClose->isClicked(mousePos, sf::Color::Red)) {//fix
            std::cout << "Close" << std::endl;
            this->window->close();
        }

        collision();
        win();
        Render();
    }
    
}


//collision detection
void Game::collision() {
    //remove it when you understand the defult collision
    //https://cdn.discordapp.com/attachments/851402748107948062/1118747029586325575/rectangle_collision.png
    //defult body collision detection
   /* if (allplayer->begin()->getPosition().x < food->getPosition().x + 20 &&
        allplayer->begin()->getPosition().x + 20 > food->getPosition().x &&
        allplayer->begin()->getPosition().y < food->getPosition().y + 20 &&
        20 + allplayer->begin()->getPosition().y > food->getPosition().y) {
        score++;
        player->grow();
    }*/
    
    // body collision unsing SFML
    for (std::list<Block>::iterator it = allplayer->begin(); it != allplayer->end(); it++) {

        if (allplayer->begin() != it) {
            if (allplayer->begin()->getPosition().x + 20 == it->getPosition().x + 20 &&
                allplayer->begin()->getPosition().y + 20 == it->getPosition().y + 20) {
                died();
            }
        }
    }
    // food collision
    sf::FloatRect intplayer(allplayer->begin()->getPosition().x, allplayer->begin()->getPosition().y,20,20);
    sf::FloatRect intfood(food->getPosition().x, food->getPosition().y, 20, 20);
    if (intplayer.intersects(intfood)) {
        score++;
        player->grow();
        spawnFood();
    }
    
    
    //window collision//
    if(allplayer->begin()->getPosition().x < 10 || allplayer->begin()->getPosition().x > 780 ||
        allplayer->begin()->getPosition().y < 10 || allplayer->begin()->getPosition().y > 680){
        died();
    }
   
}
// game end callback
void Game::died() {
    diedtext->text.setString("Game Over final score is: " + std::to_string(score));
    diedtext->text.setFillColor(sf::Color::Red);
    diedtext->shape.setSize(sf::Vector2f(diedtext->text.getGlobalBounds().width +20, 40));
    diedtext->shape.setPosition(sf::Vector2f(800 /2 - diedtext->shape.getSize().x/2 +20, 680 / 2 - diedtext->shape.getSize().y / 2 +40));
    diedtext->shape.setFillColor(sf::Color::Black);
    diedtext->shape.setOutlineThickness(-3);
    diedtext->shape.setOutlineColor(sf::Color::Red);
    // Set the position of the text relative to the shape
    float textPosX = diedtext->shape.getPosition().x + diedtext->shape.getSize().x / 2  - diedtext->text.getGlobalBounds().width / 2;
    float textPosY = diedtext->shape.getPosition().y + diedtext->shape.getSize().y / 2 - diedtext->text.getGlobalBounds().height / 2 - 5;
    diedtext->text.setPosition(sf::Vector2f(textPosX, textPosY));
    
    pause = false;
    gameEnd = true;
    btnStart->text.setString("Restart");
    sf::FloatRect textBounds = btnStart->text.getGlobalBounds();
    btnStart->text.setOrigin(textBounds.width / 2, textBounds.height / 2);
   
}
// game win
void::Game::win() {
    if (score >= 10) {
       wintext->text.setString("**Congratulations you won**");
       wintext->text.setFillColor(sf::Color(165,175,50));
       wintext->shape.setSize(sf::Vector2f(wintext->text.getGlobalBounds().width + 20, 40));
       wintext->shape.setPosition(sf::Vector2f(800 / 2 - wintext->shape.getSize().x / 2 + 20, 680 / 2 - wintext->shape.getSize().y / 2 + 40));
       wintext->shape.setFillColor(sf::Color::Black);
       wintext->shape.setOutlineThickness(-3);
       wintext->shape.setOutlineColor(sf::Color(165, 175, 50));
       // Set the position of the text relative to the shape
       float textPosX = wintext->shape.getPosition().x + wintext->shape.getSize().x / 2 - wintext->text.getGlobalBounds().width / 2;
       float textPosY = wintext->shape.getPosition().y + wintext->shape.getSize().y / 2 - wintext->text.getGlobalBounds().height / 2 - 5;
       wintext->text.setPosition(sf::Vector2f(textPosX, textPosY));

       pause = false;
       gameEnd = true;
       btnStart->text.setString("Restart");
       sf::FloatRect textBounds = btnStart->text.getGlobalBounds();
       btnStart->text.setOrigin(textBounds.width / 2, textBounds.height / 2);
    }
}
// restart game on dieth or win
void Game::restart() {
    btnStart->text.setString("Start");
    sf::FloatRect textBounds = btnStart->text.getGlobalBounds();
    btnStart->text.setOrigin(textBounds.width / 2, textBounds.height / 2);
    score = 0; // Reset the score
    allplayer->clear();
    diedtext->text.setString(""); // Clear the death message
    diedtext->shape.setSize(sf::Vector2f(0, 0));//

    wintext->text.setString("");// Clear the win message
    wintext->shape.setSize(sf::Vector2f(0, 0));//
    spawnFood(); // Respawn the food
    for (int i = 1; i <= 3; i++) {//defuld snake length
        if (i == 1) {
            allplayer->push_front(Block(sf::Vector2f(500, 500)));
        }
        else {
           //spawn body out side the game area to make sure that the body does not collide with the head 
           //the movement function will adjust the body to attach it with the head
           allplayer->push_back(Block(sf::Vector2f(-200 , -200)));
        }
    }
}
// spawn food
void Game::spawnFood() {
    if (Foodspawn) {
        do {
            // spawn inside playArea
            int x = (rand() % 35 * 20) + 20;//rand from 20X to less 700X
            int y = (rand() % 30 * 20) + 20;//rand from 20Y to less 600Y
            
            for (std::list<Block>::iterator it = allplayer->begin(); it != allplayer->end(); it++) {
                // check food that not spawn in body
                if (it->getPosition().x == food->getPosition().x && it->getPosition().y == food->getPosition().y) {
                    food->spawn(x,y);
                    Foodspawn = false;
                    break;
                }
                else {
                    Foodspawn = true;
                }
            }
        } while (Foodspawn != true);
    }
    
}
