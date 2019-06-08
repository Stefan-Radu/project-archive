#ifndef MATRIX_H
#define MATRIX_H
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;

struct chr
{
  float y1;
  sf::Text text;
  int g=150;
  int b=5;
  wchar_t a;
};

struct stream
{
  float y;
  float x;
  int length;
  float speed;
  chr arr[22];
};

class Matrix
{
  public:
    sf::RenderWindow window;
    Matrix(int ,int ,int);
    stream s[60];
    int width;
    int height;
    int csize;
    void setup();
    void update();
    void Start();
    bool MatrixOn=false;

  private:
    sf::Font font;
    sf::ContextSettings sett;


};

#endif // MATRIX_H
