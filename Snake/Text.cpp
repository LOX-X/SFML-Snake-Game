#include "Text.h"
Text::Text(sf::Vector2f pos) {
    font.loadFromFile("../External/Fonts/Lato-Black.ttf");
    text.setFont(font);
    text.setCharacterSize(22);
    text.setPosition(pos.x - text.getGlobalBounds().width, pos.y - text.getGlobalBounds().height);
}

void Text::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}