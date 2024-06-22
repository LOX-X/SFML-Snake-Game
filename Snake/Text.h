#pragma once
#include <SFML/Graphics.hpp>
class Text
{
public:
	sf::RectangleShape shape;
	sf::Font font;
	sf::Text text;
	Text(sf::Vector2f pos);
	void draw(sf::RenderWindow& window);
	
};

