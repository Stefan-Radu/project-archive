#include "Snake.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

Snake::Snake(int xaxis,int yaxis, int s,int sc):
  x(xaxis),y(yaxis),snake_size(s),scale(sc)
{
  speed=1.0f*snake_size;
  length=0;
  dir.x=0;
  dir.y=0;
  head.setSize(sf::Vector2f(snake_size,snake_size));
  head.setFillColor(sf::Color::White);
  head.setOutlineThickness(-1);
  head.setOutlineColor(sf::Color(220,220,220));
  head.setPosition(x,y);
}

void Snake::Update()
{
  for(int i=length;i>=1;i--)
  {
    if(i==1)
      body[i].setPosition(x,y);
    else
    {
      sf::Vector2f p=body[i-1].getPosition();
      body[i].setPosition(p);
    }
  }
  x+=dir.x;
  y+=dir.y;
  head.setPosition(x,y);

}

void Snake::Grow()
{
  for(int i=length+scale;i>length;i-=1)
  {
    body[i].setFillColor(sf::Color::White);
    body[i].setOutlineThickness(-1);
    body[i].setOutlineColor(sf::Color(220,220,220));
    body[i].setSize(sf::Vector2f(snake_size,snake_size));
    if(length==0)
      body[i].setPosition(x,y);
    else
    {
      sf::Vector2f p=body[length].getPosition();
      body[i].setPosition(p);
    }
  }
  length+=scale;
}

bool Snake::IsAlive()
{
  bool alive=true;
  sf::Vector2f head_position(head.getPosition());
  if(head_position.x<10)
    alive=false;
  else if(head_position.x>700)
    alive=false;
  else if(head_position.y<10)
    alive=false;
  else if(head_position.y>700)
    alive=false;

  if(alive)
  {
    for(int i=4;i<=length&&alive;i++)
    {
      sf::Vector2f body_position(body[i].getPosition());
      if(head_position==body_position)
        alive=false;
    }
  }
  if(alive)
    return true;
  else
    return false;
}
