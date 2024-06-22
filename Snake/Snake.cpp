#include "Snake.h"
#include "Block.h"
Snake::Snake()  {
	for (int i = 1; i <= 3; i++) {//defuld snake length
		array.push_front(Block(sf::Vector2f(500+(i*20), 500)));//defult spawn
	}
}

std::list<Block>& Snake::getplayer() {
    return array;
}

    /*
    * pop back
    * remove each time 1 body from snake and replace it on the next move 
    more details https://cdn.discordapp.com/attachments/851402748107948062/1118381713781956659/Created_by_LoX.png

    */
void Snake::Move(int newdirection) {
	float distance = 20; // this is distance between each body block | based on body size
    
	array.pop_back();
   
    if (newdirection == UP)
    {
        if (dir != DOWN)
        {
            array.push_front(Block(sf::Vector2f(array.front().getPosition().x, array.front().getPosition().y - distance)));
            dir = UP;
        } 
        else
        {
            array.push_front(Block(sf::Vector2f(array.front().getPosition().x, array.front().getPosition().y + distance)));
        }
    }

    else if (newdirection == RIGHT)
    {
        if (dir != LEFT)
        {
            array.push_front(Block(sf::Vector2f(array.front().getPosition().x + distance, array.front().getPosition().y)));
            dir = RIGHT;
        }
        else
        {
            array.push_front(Block(sf::Vector2f(array.front().getPosition().x - distance, array.front().getPosition().y)));
        }
    }

    else if (newdirection == DOWN)
    {
        if (dir != UP)
        {
            array.push_front(Block(sf::Vector2f(array.front().getPosition().x, array.front().getPosition().y + distance)));
            dir = DOWN;
        }
        else
        {
            array.push_front(Block(sf::Vector2f(array.front().getPosition().x, array.front().getPosition().y - distance)));
        }

    }

    else if (newdirection == LEFT)
    {
        if (dir != RIGHT)
        {
            array.push_front(Block(sf::Vector2f(array.front().getPosition().x - distance, array.front().getPosition().y)));
            dir = LEFT;
        }
        else
        {
            array.push_front(Block(sf::Vector2f(array.front().getPosition().x + distance, array.front().getPosition().y)));
        }
    }
    
}
void Snake::draw(sf::RenderWindow& window) {
    

    for (std::list<Block>::iterator it = array.begin(); it != array.end(); it++) {
        sf::Vector2f pos = it->getPosition();
        sf::RectangleShape shape = it->getShape();
        shape.setFillColor(sf::Color::Black); // snake body
        shape.move(pos);
        window.draw(shape);
    }
    std::list<Block>::iterator headIt = array.begin();
    sf::Vector2f headPos = headIt->getPosition();
    sf::RectangleShape headShape = headIt->getShape();
    headShape.setFillColor(sf::Color::Red); // snake head
    headShape.move(headPos);
    window.draw(headShape);
	
}

void Snake::grow() {
    array.push_back(Block(sf::Vector2f(array.back().getPosition().x, array.back().getPosition().y)));
}