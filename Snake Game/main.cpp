#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "Game.h"
#include "Snake.h"

using namespace std;

int main()
{
  int w=700,h=750,sc=2,s=10,b=10,m=50;//width, height, scale, size, border, margin;
  srand(time(0));//seed the rand
  Snake snake(350,350,s,sc);//initialize the snake with the its position size(fatness) and scale-aka how much it grows when it eats an apple
  Food food(w,h-m,s);//initialize the food with its position
  Game g1(w+2*b,h+2*b,snake,food);//initialize the game window with size and contained objects
  while(g1.window.isOpen())
  {
    g1.Check_Events();//escape or exit
    if(!g1.game_started)
    {
      g1.Check_Start_Events();
      g1.Show_Menu();
    }
    else
    {
      if(g1.game_over)
      {
        g1.Check_Over();//checks if the restart/ quit button are pressed
        g1.window.clear(sf::Color(15,15,15));
        g1.Show_Game_Over();
        g1.window.display();//displays the end screen
      }
      else
      {
        if(g1.ai_mode)
        {
          sf::Mouse::setPosition(sf::Vector2i(700,400));
          g1.window.setFramerateLimit(60);
          while(g1.snake.IsAlive())
          {
            g1.Check_Ai_Events();
            if(!g1.window.isOpen())
              break;// stops the loop if the window is no longer open
            g1.window.clear(sf::Color(15,15,15));
            g1.window.draw(g1.background);
            if(!g1.ok)
            {
              g1.Show_How();
            }
            else
            {
              g1.steer();
              if(!g1.is_safe())
              {
                g1.save();
                if(!g1.is_safe())
                  g1.save();
              }
              g1.snake.Update();//updates the snake position
              g1.Check_Food();//checks if the food was eaten
              if(g1.food_eaten)
              {
                while(!g1.OkPlace())
                  g1.food.Update();//if the food was eaten search for a new location
                g1.snake.Grow();//grow snake
                g1.food_eaten=false;
                g1.score+=g1.snake.scale;
              }
            }
            g1.window.draw(g1.snake.head);
            for(int i=1;i<=g1.snake.length;i++)
              g1.window.draw(g1.snake.body[i]);
            g1.window.draw(g1.food.apple);
            if(g1.snake.dir.x!=0||g1.snake.dir.y!=0)
              g1.Show_Score();
            g1.window.display();//displays the in-game frames
          }
          if(!g1.snake.IsAlive())
          {
            g1.window.setFramerateLimit(13);
            g1.Death();//death animation
            g1.game_over=true;//mark the game as over
          }
        }
        else if(!g1.ai_mode)
        {
          while(g1.snake.IsAlive())
          {
            if(g1.snake.dir.x==0&&g1.snake.dir.y==0)
              g1.window.setFramerateLimit(60);
            else
              g1.window.setFramerateLimit(15);
            g1.Check_Snake_Events();//checks snake movement and escape button presses
            if(!g1.window.isOpen())
              break;// stops the loop if the window is no longer open
            g1.window.clear(sf::Color(15,15,15));
            g1.window.draw(g1.background);
            g1.snake.Update();//updates the snake position
            g1.Check_Food();//checks if the food is eaten
            if(g1.food_eaten)
            {
              while(!g1.OkPlace())
                g1.food.Update();//if the food was eaten search for a new location
              g1.snake.Grow();//grow snake
              g1.food_eaten=false;
              g1.score+=g1.snake.scale;
            }
            g1.window.draw(g1.snake.head);
            for(int i=1;i<=g1.snake.length;i++)
              g1.window.draw(g1.snake.body[i]);
            g1.window.draw(g1.food.apple);
            if(g1.snake.dir.x!=0||g1.snake.dir.y!=0)
            {
              g1.Show_Score();
              g1.Update_Highscore();
              g1.Show_Highscore();
            }
            else
              g1.Show_How();
            g1.window.display();//displays the in-game frames
          }
          if(!g1.snake.IsAlive())
          {
            g1.Death();//death animation
            g1.game_over=true;//mark the game as over
          }
        }
      }
    }
  }
}
