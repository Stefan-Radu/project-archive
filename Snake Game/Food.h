#ifndef FOOD_H
#define FOOD_H
#include <SFML/Graphics.hpp>

class Food
{
  public:
    Food(int, int, int);
    int food_size;
    sf::CircleShape apple;
    int x;
    int y;
    void Update();
  private:
    int width;
    int height;
};

#endif // FOOD_H
