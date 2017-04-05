// Author:	Joe Ruiz
// Spring 2017
// CS 3350 Software Engineering
// My contributions to the game "Engage Hyperdrive" aka Space Escape
//
//
// Gravity Formula from stackoverflow
/*float g = 9.8f;
  float gravity(Vec p1_pos, Vec p2_pos, float p1_mass, float p2_mass)
  {
  float distance = (p2_pos - p1_pos); 
  return g * p1_mass * p2_mass / (distance * distance);
  }
  */

#include <GL/glx.h>
#include "fonts.h"

extern int restart;

void pauseGame(int x, int y, Rect pausebox)
{
    glColor3f(0.0, 0.0, 0.0);

    float cx = x/2;
    int cy = y/2;
    glBegin(GL_QUADS);
    glVertex2i(cx - 150, cy + 75);
    glVertex2i(cx + 150, cy + 75);
    glVertex2i(cx + 150, cy - 75);
    glVertex2i(cx - 150, cy - 75);
    glEnd();
    glEnable(GL_TEXTURE_2D);

    pausebox.bot = cy + 30;
    pausebox.left = cx - 110;
    pausebox.center = 0;
    ggprint16(&pausebox, 25, 0x00ffffff, "GAME PAUSED...");
    ggprint12(&pausebox, 20, 0x00ffffff, "Press P to Resume");
    ggprint12(&pausebox, 20, 0x00ffffff, "Press R to Restart Level");
    ggprint12(&pausebox, 20, 0x00ffffff, "Press L to Restart LVL1 --Soon");
    ggprint12(&pausebox, 20, 0x00ffffff, "Press E to Exit Game");
    glEnable(GL_TEXTURE_2D);

}

void restartLevel(int &health, float &fuel, int &bulletsRemain)
{
    health = 300;
    fuel = 300;
    bulletsRemain = 50;

}

void deadGame(int x, int y, Rect pausebox)
{
    glColor3f(0.0, 0.0, 0.0);

    float cx = x/2;
    int cy = y/2;
    glBegin(GL_QUADS);
    glVertex2i(cx - 150, cy + 75);
    glVertex2i(cx + 150, cy + 75);
    glVertex2i(cx + 150, cy - 75);
    glVertex2i(cx - 150, cy - 75);
    glEnd();
    glEnable(GL_TEXTURE_2D);

    pausebox.bot = cy + 30;
    pausebox.left = cx - 110;
    pausebox.center = 0;
    ggprint16(&pausebox, 25, 0x00ffffff, "YOU ARE DEAD!");
    ggprint16(&pausebox, 25, 0x00ffffff, "You hit too many objects!");
    ggprint12(&pausebox, 20, 0x00ffffff, "Press R to Restart Level");
    ggprint12(&pausebox, 20, 0x00ffffff, "Press L to Restart LVL1 --Soon");
    ggprint12(&pausebox, 20, 0x00ffffff, "Press E to Exit Game");
    glEnable(GL_TEXTURE_2D);

}

void strandedGame(int x, int y, Rect pausebox)
{
    glColor3f(0.0, 0.0, 0.0);

    float cx = x/2;
    int cy = y/2;
    glBegin(GL_QUADS);
    glVertex2i(cx - 150, cy + 75);
    glVertex2i(cx + 150, cy + 75);
    glVertex2i(cx + 150, cy - 75);
    glVertex2i(cx - 150, cy - 75);
    glEnd();
    glEnable(GL_TEXTURE_2D);

    pausebox.bot = cy + 30;
    pausebox.left = cx - 110;
    pausebox.center = 0;
    ggprint16(&pausebox, 25, 0x00ffffff, "YOU ARE STRANDED!");
    ggprint16(&pausebox, 25, 0x00ffffff, "You are out of fuel!");
    ggprint12(&pausebox, 20, 0x00ffffff, "Press R to Restart Level");
    ggprint12(&pausebox, 20, 0x00ffffff, "Press L to Restart LVL1 --Soon");
    ggprint12(&pausebox, 20, 0x00ffffff, "Press E to Exit Game");
    glEnable(GL_TEXTURE_2D);

}


