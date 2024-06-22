#include "Block.h"
Block::Block(sf::Vector2f position) {
	this->position = position;
	shape.setSize(sf::Vector2f(20, 20));
};

sf::Vector2f Block::getPosition() {
	return position;
}

sf::RectangleShape& Block::getShape() {
	return shape;
}

