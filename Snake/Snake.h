#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Block.h"
#include "Food.h"
class Snake 
{
private: 
	std::list<Block> array;
	enum direction { UP, RIGHT, DOWN, LEFT };
	int dir;
	Food* food;
public: 
	Snake();
	std::list<Block>& getplayer();
	void Move(int newdirection);
	void draw(sf::RenderWindow& window);
	void grow();
};

