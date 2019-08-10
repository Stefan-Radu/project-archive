#include "Matrix.h"
#include <bits/stdc++.h>
using namespace std;

Matrix::Matrix(int w,int h,int c):
  width(w),height(h),csize(c)
{
  srand(time(0));
  font.loadFromFile("KozMinPro-Regular.otf");
  sett.antialiasingLevel=8;
}

void Matrix::setup()
{
  window.create(sf::VideoMode(width,height),"MATRIX",sf::Style::Default,sett);
  for(int j=0;j<width/csize;j+=1)
  {
    s[j].y=-10-rand()%21;
    s[j].x=j*csize;
    s[j].length=rand()%16+7;
    for(int i=0;i<s[j].length;i++)
    {
      s[j].arr[i].y1=s[j].y-i*csize;
      s[j].arr[i].text.setFont(font);
      s[j].arr[i].text.setCharacterSize(csize);
      if(rand()%2==0&&i==0)
        s[j].arr[i].text.setFillColor(sf::Color(120,255,217));
      else
        s[j].arr[i].text.setFillColor(sf::Color(255,s[j].arr[i].g+3*i,s[j].arr[i].b+3*i));
      s[j].arr[i].a=L'ア';
      s[j].arr[i].text.setString(s[j].arr[i].a);
      s[j].arr[i].text.setPosition(s[j].x,s[j].arr[i].y1);
      s[j].speed=(float)(rand()%11+6)/100;
    }
  }
}

void Matrix::update()
{
  for(int j=0;j<width/csize;j+=1)
    {

      for(int i=0;i<s[j].length;i++)
      {
        if(s[j].arr[i].y1<=height)
          s[j].arr[i].y1+=s[j].speed;
        else
        {
          s[j].arr[i].y1=-csize;
          if(i==s[j].length-1)
            s[j].speed=(float)(rand()%11+6)/100;
        }
        if(rand()%1001==257)
        {
          s[j].arr[i].a=L'ア'+rand()%93;
          s[j].arr[i].text.setString(s[j].arr[i].a);
        }
        s[j].arr[i].text.setPosition(s[j].x,s[j].arr[i].y1);

        window.draw(s[j].arr[i].text);
      }
    }
}

void Matrix::Start()
{
  sf::Text start;
  start.setFont(font);
  start.setFillColor(sf::Color(255,160,0));
  start.setCharacterSize(48);
  start.setString("Press any key to start");
  start.setPosition(320,height/2-48);
  window.draw(start);
}
