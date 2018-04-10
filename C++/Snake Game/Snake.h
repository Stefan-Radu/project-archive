#ifndef SNAKE_H
#define SNAKE_H
#include <SFML/Graphics.hpp>

struct Dir
{
  int x;
  int y;
};

class Snake
{
  public:
    Snake(int, int, int, int);
    int x;
    int y;
    int scale;//how much it grows when it eats one apple
    float speed;
    int snake_size;
    int length;
    Dir dir;
    sf::RectangleShape body[2000];
    sf::RectangleShape head;
    void Update();
    void Grow();
    bool IsAlive();
};
#endif // SNAKE_H
