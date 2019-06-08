#include <SFML/Graphics.hpp>
#include <iostream>
#include "Matrix.h"

using namespace std;

int main()
{
    Matrix m1(1080,720,24);
    m1.setup();
    while(m1.window.isOpen())
    {
      sf::Event event;
      while(m1.window.pollEvent(event))
      {
        if(event.type==sf::Event::Closed)
          m1.window.close();
        else if(event.type==sf::Event::KeyPressed)
          m1.MatrixOn=true;
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
          m1.window.close();
      }
      m1.window.clear(sf::Color::Black);
      if(!m1.MatrixOn)
        m1.Start();
      else
        m1.update();
      m1.window.display();
    }
}
