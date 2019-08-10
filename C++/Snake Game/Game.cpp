#include "Game.h"
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

Game::Game(int w,int h,Snake s,Food f):
  width(w),height(h),snake(s),food(f)
{
  sett.antialiasingLevel=8;
  window.create(sf::VideoMode(width,height),"Snake Game",sf::Style::Close,sett);
  food_eaten=false;
  game_over=false;
  game_started=false;
  ai_mode=false;
  ok=false;
  if(!texture1.loadFromFile("resources/Replay Button.png"))
    cout<<"lag1";
  if(!texture2.loadFromFile("resources/Off Button.png"))
    cout<<"lag2";
  if(!texture3.loadFromFile("resources/Play Button.png"))
    cout<<"lag3";
  if(!texture4.loadFromFile("resources/AI Button.png"))
    cout<<"lag4";
  if(!texture5.loadFromFile("resources/Menu Button.png"))
    cout<<"lag5";
  background.setFillColor(sf::Color(15,25,25));
  background.setOutlineColor(sf::Color(255, 255, 255));
  background.setOutlineThickness(2);
  background.setSize(sf::Vector2f(700,700));
  background.setPosition(10,10);
  font.loadFromFile("arialbd.ttf");
  score=0;
  c=165;
  u=5;
  highscore=0;
  replay.setTexture(texture1);
  turn_off.setTexture(texture2);
  play.setTexture(texture3);
  ai.setTexture(texture4);
  menu.setTexture(texture5);
}

void Game::Check_Events()
{
  if(window.pollEvent(event))
  {
    if(event.type==sf::Event::Closed)
      window.close();
    else if(event.type==sf::Event::KeyPressed)
    {
      if(event.key.code==sf::Keyboard::Escape)
        window.close();
    }
  }
}
void Game::Check_Snake_Events()
{
  if(window.pollEvent(event))
  {
    if(event.type==sf::Event::Closed)
      window.close();
    else if(sf::Event::KeyPressed)
      if(event.key.code==sf::Keyboard::Escape)
        window.close();
    else if(event.type==sf::Event::KeyPressed)
    {
      switch(event.key.code)
      {
      case sf::Keyboard::Up:
        {
          if(snake.dir.y!=snake.speed)
          {
            snake.dir.x=0;
            snake.dir.y=-snake.speed;
          }
        }break;
      case sf::Keyboard::Down:
        {
          if(snake.dir.y!=-snake.speed)
          {
            snake.dir.x=0;
            snake.dir.y=snake.speed;
          }
        }break;
      case sf::Keyboard::Right:
        {
          if(snake.dir.x!=-snake.speed)
          {
            snake.dir.x=snake.speed;
            snake.dir.y=0;
          }
        }break;
      case sf::Keyboard::Left:
        {
          if(snake.dir.x!=snake.speed)
          {
            snake.dir.x=-snake.speed;
            snake.dir.y=0;
          }
        }break;
      }
    }
  }
}

void Game::Check_Ai_Events()
{
  while(window.pollEvent(event))
  {
    if(event.type==sf::Event::Closed)
      window.close();
    else if(event.type==sf::Event::KeyPressed)
      if(event.key.code==sf::Keyboard::Return)
        ok=true;
      else if(event.key.code==sf::Keyboard::Escape)
        window.close();

  }
}

void Game::Check_Food()
{
  if(abs(snake.x-food.x)<1&&abs(snake.y-food.y)<1)
    food_eaten=true;
}

bool Game::OkPlace()
{
  bool ok=true;
    for(int i=1;i<=snake.length&&ok;i++)
    {
      sf::Vector2f p1=snake.body[i].getPosition();
      sf::Vector2f p2(food.x,food.y);
      if(p1==p2)
        ok=false;
    }
    if(ok)
    {
      sf::Vector2f p1(food.x,food.y);
      sf::Vector2f p2(snake.x,snake.y);
      if(p1==p2)
        ok=false;
    }
    if(ok)
      return true;
    else
      return false;
}

void Game::Show_Score()
{
  sf::Text t1,t2;
  char s[50];
  int c=score;
  int i;
  if(c<10)
    i=0;
  else
  {
    i=0;
    while(c>=10)
    {
      c/=10;
      i++;
    }
  }
  c=score;
  s[i+1]='\0';
  for(int j=i;j>=0;j--)
  {
    s[j]=c%10+48;
    c/=10;
  }

  t1.setFont(font);
  t1.setFillColor(sf::Color::White);
  t1.setCharacterSize(35);
  t1.setString("Score: ");
  t1.setPosition(30,718);
  t2.setFont(font);
  t2.setFillColor(sf::Color::White);
  t2.setCharacterSize(33);
  t2.setString(s);
  t2.setPosition(145,721);
  window.draw(t1);
  window.draw(t2);
}

void Game::Show_Highscore()
{
  sf::Text t1,t2;
  char s[50];
  int c=highscore;
  int i;
  if(c<10)
    i=0;
  else
  {
    i=0;
    while(c>=10)
    {
      c/=10;
      i++;
    }
  }
  c=highscore;
  s[i+1]='\0';
  for(int j=i;j>=0;j--)
  {
    s[j]=c%10+48;
    c/=10;
  }
  t1.setFont(font);
  t1.setCharacterSize(35);
  t1.setFillColor(sf::Color::White);
  t1.setString("Highscore: ");
  t1.setPosition(430,718);
  t2.setFont(font);
  t2.setFillColor(sf::Color::White);
  t2.setCharacterSize(33);
  t2.setString(s);
  t2.setPosition(615,721);
  window.draw(t1);
  window.draw(t2);
}

void Game::Death()
{
  int time=25;
  int k;
  sf::Vector2f p1(snake.x,snake.y);
  sf::Vector2f p2;
  bool ok=false;
  for(int i=3;i<=snake.length&&!ok;i++)
  {
    p2=snake.body[i].getPosition();
    if(p1==p2)
    {
      ok=true;
      k=i;
    }
  }
  for(int i=1;i<=time;i++)
  {
    window.clear(sf::Color(15,15,15));
    window.draw(background);
    if(i%5==0)
    {
      window.draw(snake.head);
      if(ok)
        window.draw(snake.body[k]);
    }
    for(int i=1;i<=snake.length;i++)
    {
      sf::Vector2f p3(snake.body[i].getPosition());
      if(p3!=p2||!ok)
        window.draw(snake.body[i]);
    }
    window.draw(food.apple);
    Show_Score();
    Show_Highscore();
    window.display();
  }
}

void Game::Show_Game_Over()
{
  window.draw(background);
  Show_Score();
  Show_Highscore();
  sf::Text t1;
  t1.setFont(font);
  t1.setFillColor(sf::Color::White);
  t1.setCharacterSize(50);
  t1.setString("GAME OVER");
  t1.setPosition(210,120);
  window.draw(t1);
  replay.setScale(0.12,0.12);
  replay.setPosition(345,300);
  menu.setScale(0.1175,0.1175);
  menu.setPosition(345,400);
  turn_off.setScale(0.12,0.12);
  turn_off.setPosition(345,500);
  window.draw(replay);
  window.draw(menu);
  window.draw(turn_off);
}

void Game::Check_Over()
{
  sf::Vector2i mouse=sf::Mouse::getPosition(window);
  sf::Vector2f r=replay.getPosition();
  sf::Vector2f q=turn_off.getPosition();
  sf::Vector2f m=menu.getPosition();
  if(mouse.x>=r.x&&mouse.x<=r.x+50&&mouse.y>=r.y&&mouse.y<=r.y+50)
  {
    replay.setColor(sf::Color(255,175,0));
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      game_over=false;
      food.Update();
      snake.x=350;
      snake.y=350;
      snake.length=0;
      snake.head.setPosition(snake.x,snake.y);
      snake.dir.x=0.0f;
      snake.dir.y=0.0f;
      score=0;
    }
  }
  else
    replay.setColor(sf::Color::White);
  if(mouse.x>=q.x&&mouse.x<=q.x+50&&mouse.y>=q.y&&mouse.y<=q.y+50)
  {
    turn_off.setColor(sf::Color(255,175,0));
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
      window.close();
  }
  else
    turn_off.setColor(sf::Color::White);
  if(mouse.x>=m.x&&mouse.x<=m.x+45&&mouse.y>=m.y&&mouse.y<=m.y+45)
  {
    menu.setColor(sf::Color(255,175,0));
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      game_started=false;
      ai_mode=false;
      game_over=false;
      food.Update();
      snake.x=350;
      snake.y=350;
      snake.length=0;
      snake.head.setPosition(snake.x,snake.y);
      snake.dir.x=0.0f;
      snake.dir.y=0.0f;
      score=0;
    }
  }
  else
    menu.setColor(sf::Color::White);
}

void Game::Update_Highscore()
{
  if(score > highscore)
    highscore=score;
}

void Game::Check_Start_Events()
{
  sf::Vector2i m=sf::Mouse::getPosition(window);
  sf::Vector2f p=play.getPosition();
  sf::Vector2f q=turn_off.getPosition();
  sf::Vector2f a=ai.getPosition();
  if(m.x>=p.x&&m.x<=p.x+45&&m.y>=p.y&&m.y<=p.y+45)
  {
    play.setColor(sf::Color(255,175,0));
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
       game_started=true;
       ai_mode=false;
    }
  }
  else
  {
     play.setColor(sf::Color::White);
    if(m.x>=q.x&&m.x<=q.x+50&&m.y>=q.y&&m.y<=q.y+50)
    {
      turn_off.setColor(sf::Color(255,175,0));
      if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        window.close();
    }
    else
    {
      turn_off.setColor(sf::Color::White);
      if(m.x>=a.x&&m.x<=a.x+47&&m.y>=a.y&&m.y<=a.y+47)
      {
        ai.setColor(sf::Color(255,175,0));
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
          game_started=true;
          ai_mode=true;
        }
      }
      else
        ai.setColor(sf::Color::White);

    }
  }
}

void Game::Show_Menu()
{
  sf::Text t;
  t.setFont(font);
  t.setCharacterSize(50);
  t.setPosition(230,70);
  t.setString("Snake game");
  t.setColor(sf::Color::White);
  window.clear(sf::Color(15,15,15));
  play.setScale(0.1075,0.1075);
  play.setPosition(353,260);
  ai.setScale(0.12,0.12);
  ai.setPosition(350,380);
  turn_off.setPosition(352,500);
  turn_off.setScale(0.12,0.12);
  window.draw(background);
  window.draw(t);
  window.draw(play);
  window.draw(ai);
  window.draw(turn_off);
  window.display();
}

void Game::Show_How()
{
  sf::Text t;
  t.setFont(font);
  t.setFillColor(sf::Color(c,c,c));
  t.setCharacterSize(30);
  if(u>0&&c<255)
    c+=u;
  else if(c==255)
  {
    u*=(-1);
    c+=u;
  }
  if(c>15&&u<0)
    c+=u;
  else if(c==15)
  {
    u*=(-1);
    c+=u;
  }
  if(!ai_mode&&game_started)
  {
    t.setString("Press any arrow to start");
    t.setPosition(200,720);
    window.draw(t);
  }
  else if(ai_mode&&game_started)
  {
    t.setString("Press Enter to start");
    t.setPosition(240,720);
    window.draw(t);
  }
}

bool Game::can_get_x()
{
  if((snake.x<food.x&&snake.dir.x<0)||(snake.x>food.x&&snake.dir.x>0))
    return false;
  else
    return true;
}

void Game::get_x()
{
  if(snake.x<food.x)
    snake.dir.x=snake.speed;
  else
    snake.dir.x=-snake.speed;

  snake.dir.y=0;
}

void Game::get_y()
{
  if(snake.y<food.y)
    snake.dir.y=snake.speed;
  else
    snake.dir.y=-snake.speed;
  snake.dir.x=0;
}

void Game::steer()
{
  if(snake.x==food.x)
    get_y();
  else if(snake.y==food.y)
    get_y();
  else if(snake.x!=food.x&&snake.y!=food.y)
  {
    if(can_get_x())
      get_x();
    else get_y();
  }
}

bool Game::is_safe()
{
  if(snake.dir.x!=0)
  {
    bool ok=true;
    for(int i=1;i<=snake.length&&ok;i++)
    {
      sf::Vector2f v=snake.body[i].getPosition();
      if(v.x==snake.x+snake.dir.x&&v.y==snake.y)
        ok=false;
    }
    if(ok)
      if(snake.x+snake.dir.x<5||snake.x+snake.dir.x>705)
        ok=false;
    return ok;
  }
  else
  {
    bool ok=true;
    for(int i=1;i<=snake.length&&ok;i++)
    {
      sf::Vector2f v=snake.body[i].getPosition();
      if(v.y==snake.y+snake.dir.y&&v.x==snake.x)
        ok=false;
    }
    if(ok)
      if(snake.y+snake.dir.y<5||snake.y+snake.dir.y>705)
        ok=false;
    return ok;
  }
}

void Game::save()
{
  if(snake.dir.x!=0)
  {
    bool ok1=true;
    bool ok2=true;
    bool ok3=true;
    for(int i=1;i<=snake.length;i++)
    {
      sf::Vector2f v=snake.body[i].getPosition();
      if(snake.x==v.x&&snake.y>v.y)
      {
        ok1=false;
        if(snake.y-snake.speed==v.y)
          ok3=false;
      }
      else if(snake.x==v.x&&snake.y<v.y)
        ok2=false;
    }
    if(ok1)
    {
      snake.dir.x=0;
      snake.dir.y=-snake.speed;
    }
    else if(ok2)
    {
      snake.dir.x=0;
      snake.dir.y=snake.speed;
    }
    else if(ok3)
    {
      snake.dir.x=0;
      snake.dir.y=-snake.speed;
    }
    else if(!ok3)
    {
      snake.dir.x=0;
      snake.dir.y=snake.speed;
    }
  }
  else
  {
    bool ok1=true;
    bool ok2=true;
    bool ok3=true;
    for(int i=1;i<=snake.length;i++)
    {
      sf::Vector2f v=snake.body[i].getPosition();
      if(snake.y==v.y&&snake.x>v.x)
      {
        ok1=false;
        if(snake.x-snake.speed==v.x)
          ok3=false;
      }
      else if(snake.y==v.y&&snake.x<v.x)
        ok2=false;
    }
    if(ok1)
    {
      snake.dir.y=0;
      snake.dir.x=-snake.speed;
    }
    else if(ok2)
    {
      snake.dir.y=0;
      snake.dir.x=snake.speed;
    }
    else if(ok3)
    {
      snake.dir.y=0;
      snake.dir.x=-snake.speed;
    }
    else if(!ok3)
    {
      snake.dir.y=0;
      snake.dir.x=snake.speed;
    }
  }
}























