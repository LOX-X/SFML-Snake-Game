#include "Food.h"

Food::Food() {
	shape.setSize(sf::Vector2f(20, 20));
	shape.setFillColor(sf::Color::Blue);
};
	
void Food::spawn(float x, float y) {
	position.x = x;
	position.y = y;
	shape.setPosition(position);
}

sf::Vector2f Food::getPosition() {
	return position;
}


sf::RectangleShape& Food::getShape() {
	return shape;
}