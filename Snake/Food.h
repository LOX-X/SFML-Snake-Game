#pragma once
#include <SFML/Graphics.hpp>
class Food {
private:
	sf::Vector2f position;
	sf::RectangleShape shape;
public:
	Food();
	void spawn(float x, float y);
	sf::Vector2f getPosition();
	sf::RectangleShape& getShape();
};
