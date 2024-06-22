#include "Button.h"
#include <iostream>
Button::Button(sf::Vector2f position, std::string buttonText, sf::Color bgColor) {
    shape.setPosition(position);// button position
    shape.setSize(sf::Vector2f( 110, 30));//button size
    shape.setOutlineThickness(2);//Thickness
    shape.setOutlineColor(sf::Color::White);//outline color
    shape.setFillColor(bgColor);//button color
    font.loadFromFile("../External/Fonts/Lato-Black.ttf");//font must install/ in font folder instal the font you want to use
    text.setFont(font);
    text.setString(buttonText);//button text
    text.setCharacterSize(22);//font size
    text.setFillColor(sf::Color::Black);//text color
    sf::FloatRect textBounds = text.getGlobalBounds();
    text.setOrigin(textBounds.width / 2, textBounds.height / 2);//text center
    text.setPosition(//text position
       position.x + shape.getSize().x / 2,
       position.y + shape.getSize().y / 2);
};

bool Button::isClicked(sf::Vector2f mousePos, sf::Color color) {//check if button is clicked
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (shape.getGlobalBounds().contains(mousePos)) {
            shape.setOutlineColor(color);
            return true;
        }
        else return false;
    }
    else {
        shape.setOutlineColor(sf::Color::White);
        return false;
    }
}
void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);

}