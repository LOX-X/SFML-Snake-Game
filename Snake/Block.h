#pragma once
#include <SFML/Graphics.hpp>
class Block
{
private:
	sf::Vector2f position;
	sf::RectangleShape shape;
public:
	Block(sf::Vector2f position);
	sf::Vector2f getPosition();
	sf::RectangleShape& getShape();
	
};

