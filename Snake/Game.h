
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Button.h"
#include "Food.h"
#include "Text.h"
#include "Trackbar.h"
class Game
{
    int width;
    int height;
    bool pause = false;
    bool Foodspawn = true;
    bool gameEnd = false;
    int score = 0;
    Snake* player;
    Food* food;
    Text* scoretext;
    Text* diedtext;
    Text* wintext;
    Trackbar* trackbar;
    std::list<Block>* allplayer;
    sf::RenderWindow* window;
    enum direction {UP,RIGHT,DOWN,LEFT};

    int dir;
public:
    Game(int width,int height);
    void Render();
    void Update();
    void collision();
    void spawnFood();
    void restart();
    void died();
    void win();
    void PlayArea(sf::RenderWindow& window);
    Button* btnStart;
    Button* btnStop;
    Button* btnClose;
};

