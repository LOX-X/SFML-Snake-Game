#pragma once
#include <SFML/Graphics.hpp>
class Trackbar
{
private:
    sf::RectangleShape track;
    sf::RectangleShape slider;
    bool dragging = false;
    sf::Text valueText;
    sf::Font font;

public:
    Trackbar(sf::Vector2f pos);

    void draw(sf::RenderWindow& window);
    void handleEvent(sf::Event& event);
    void update(sf::Vector2f mousePos);
    int getValue();
};

