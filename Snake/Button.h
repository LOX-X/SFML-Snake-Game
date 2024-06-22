#include <SFML/Graphics.hpp>

struct Button  {
public:
    sf::Text text;
    sf::Font font;
    sf::RectangleShape shape;

    // constructor to initialize the button
    Button(sf::Vector2f position, std::string buttontext, sf::Color bgcolor);

    // function to check if the button is clicked
    bool isClicked(sf::Vector2f mousepos, sf::Color color);

    // function to draw the button
    void draw(sf::RenderWindow& window);
};


