#include "Food.h"
#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>

Food::Food(int w, int h, int f):
  food_size(f),width(w), height(h)
{
  apple.setRadius(food_size/2);
  apple.setFillColor(sf::Color::Red);
  x=(rand()%(width/food_size)+1)*food_size;
  y=(rand()%(height/food_size)+1)*food_size;
  apple.setPosition(x,y);
}


void Food::Update()
{
  x=(rand()%(width/food_size)+1)*food_size;
  y=(rand()%(height/food_size)+1)*food_size;
  apple.setPosition(x,y);
}

