#ifndef GAME_H
#define GAME_H
#include "Snake.h"
#include "Food.h"
#include <fstream>

using namespace std;

class Game
{
  public:
    Game(int, int, Snake, Food);
    bool food_eaten;
    bool game_over;
    bool game_started;
    bool ai_mode;
    int score;
    sf::RenderWindow window;
    Snake snake;
    Food food;
    sf::RectangleShape background;
    void Check_Snake_Events();
    void Check_Events();
    void Check_Food();
    void Check_Start_Events();
    void Check_Ai_Events();
    bool OkPlace();//food
    void Death();
    void Show_Score();
    void Show_Game_Over();
    void Check_Over();
    sf::Texture texture1;
    sf::Texture texture2;
    sf::Texture texture3;
    sf::Texture texture4;
    sf::Texture texture5;
    sf::Sprite replay;
    sf::Sprite turn_off;
    sf::Sprite play;
    sf::Sprite ai;
    sf::Sprite menu;
    void Update_Highscore();
    void Show_Highscore();
    void Show_Menu();
    void Show_How();
    void get_x();
    void get_y();
    bool can_get_x();
    void steer();
    bool is_safe();
    void save();
    bool ok;
  private:
    sf::ContextSettings sett;
    sf::Event event;
    sf::Font font;
    int width;
    int height;
    int highscore;
    int c;
    int u;
};


#endif // GAME_H
