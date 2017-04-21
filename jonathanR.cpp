/* Jonathan Roman
 *
 * This is the code I have contributed to 
 * my groups project.
 */
#include<iostream>
#include <GL/glx.h>
#include <cmath>
#include "typedefine.h"
#include <unistd.h>
#include <ctime>

void astronautCollision(Game *g, int &health)
{
    Asteroid *a = g->ahead;
    // Attempt to detect collision between asteroid and
    // astronaut
    Flt d2, d3, dist2;
    Flt d4, d5, dist4;
    Flt d6, d7, dist6;
    while(a){
	d2 = g->astronaut.pos[0] - a->pos[0];
	d3 = g->astronaut.pos[1] - a->pos[1];
	dist2 = (d2*d2 + d3*d3);

	d4 = g->astronaut.pos[0] - a->pos[0];
	d5 = (g->astronaut.pos[1]+20) - a->pos[1];
	dist4 = (d4*d4 + d5*d5);

	if (dist2 < (a->radius)*(a->radius) || dist4 < (a->radius)*(a->radius)) {
	    //std::cout << "asteroid hit." << std::endl;
	    //this asteroid is hit.

	    // Reducing health when hitting an asteroid.
	    if (health >= 0){
		health = health - 120;
		// So that health display does not show 
		// a negative number.
		if (health < 0) {
		    health = 0;
		}
	    }
	    if (a->radius > MINIMUM_ASTEROID_SIZE) {
		//break it into pieces.
		Asteroid *ta = a;
		buildAsteroidFragment(ta, a); 
		int r = rand()%10+5;
		for (int k=0; k<r; k++) {
		    //get the next asteroid position in the array
		    Asteroid *ta = new Asteroid;
		    buildAsteroidFragment(ta, a); 
		    //add to front of asteroid linked list
		    ta->next = g->ahead;
		    if (g->ahead != NULL)
			g->ahead->prev = ta; 
		    g->ahead = ta; 
		    g->nasteroids++;
		}
	    } else {
		a->color[0] = 1.0;
		a->color[1] = 0.1;
		a->color[2] = 0.1;
		//asteroid is too small to break up
		//delete the asteroid and bullet
		Asteroid *savea = a->next;
		deleteAsteroid(g, a); 
		a = savea;
		g->nasteroids--;
	    }

	}
	if (a == NULL)
	    break;
	a = a->next;
    }   
    // End attempt...
}

// Used to display how much fuel is left and decreases as it
// is used..
void fuelbar(int x, int y, Rect r, float &fuel)
{
    float fuelView = fuel;// - 150;
    // glDisable(GL_TEXTURE_2D);
    glColor3f(0.01,0.23,0.25);
    float cx = x;
    //int cy = y;
    glBegin(GL_QUADS);

    glVertex2i(cx-155,80);
    glVertex2i(cx+155,80);
    glVertex2i(cx+155,50);
    glVertex2i(cx-155,50);
    glEnd();
    glEnable(GL_TEXTURE_2D);
    glColor3f(0.0,1.0,0.0);
    if (fuel <= 50) {
	glColor3f(1.0,0.0,0.0);
    }

    // Setting up location of box
    glBegin(GL_QUADS);
    glVertex2i(cx-150,75);
    glVertex2i(cx+fuelView-150,75);
    glVertex2i(cx+fuelView-150,55);
    glVertex2i(cx-150,55);
    glEnd();
    r.bot = 60;
    r.left = cx ;
    r.center = 1;
    //glEnable(GL_TEXTURE_2D);		If you want to see amount
    ggprint8b(&r,20,0x00ffffff, "Fuel");//%d", (int)fuel);
    glEnable(GL_TEXTURE_2D);

}

// Used to determin if astronaut has fuel to use
int fuelRemains(float fuel)
{
    if (fuel > 0)
	return 1;
    else
	return 0;
}
// Reduces the fuel the astronaut has left
float reduceFuel(float fuel)
{
    fuel = fuel - .1;
    //So that fuel does not go negative..
    if (fuel < 0) {
	fuel = 0;
    }
    return fuel;
}
// Used to determin if atronaut has bullets
// to shoot
int remainingAmo(int bulletsRemain)
{
    if (bulletsRemain > 0) {
	return 1;
    }
    else {
	return 0;
    }
}
// Reduces number of bullets remaining
int reduceAmo(int bulletsRemain)
{
    return --bulletsRemain;
}

int getHealthPack(Game *g, HealthBox *healthbox, int &health)
{
    // Attempt to detect collision between health pach and
    // astronaut
    Flt d2, d3, dist2;
    d2 = g->astronaut.pos[0] - healthbox->pos[0];
    d3 = g->astronaut.pos[1] - healthbox->pos[1];
    dist2 = (d2*d2 + d3*d3);
    if (dist2 < healthbox->radius*healthbox->radius) {
	// You can come into the radius of the healthbox
	health += 50;
	return 1;
    }
    return 0;
}
int getFuelPack(Game *g, FuelBox *fuelbox, float &fuel)
{
    // Attempt to detect collision between fuel pack and
    // astronaut
    Flt d2, d3, dist2;
    d2 = g->astronaut.pos[0] - fuelbox->pos[0];
    d3 = g->astronaut.pos[1] - fuelbox->pos[1];
    dist2 = (d2*d2 + d3*d3);
    if (dist2 < fuelbox->radius*fuelbox->radius) {
	// You can come into the radius of the fuel pack
	fuel += 100;
	return 1;
    }
    return 0;
}

int getAmoPack(Game *g, AmoBox *amobox, int &bulletsRemain)
{
    // Attempt to detect collision between amo pack and
    // astronaut
    Flt d2, d3, dist2;
    d2 = g->astronaut.pos[0] - amobox->pos[0];
    d3 = g->astronaut.pos[1] - amobox->pos[1];
    dist2 = (d2*d2 + d3*d3);
    if (dist2 < amobox->radius*amobox->radius) {
	// You can come into the radius of the amo pack
	bulletsRemain += 15;
	return 1;
    }
    return 0;
}

// Initialize the values of the FuelBox struct
void buildFuelBox(FuelBox *f)
{
    f->radius = 45;
    f->angle = 0.0f;
    f->pos[0] = 100;//(Flt)(rand() % xres);
    f->pos[1] = 100;//(Flt)(rand() % xres);
    f->pos[2] = 0.0f;
    f->angle = 0.0;

    f->rotate = rnd() * 4.0 - 2.0;

    f->vel[0] = (Flt)(rnd()/2);
    f->vel[1] = (Flt)(rnd()/2);    

}

// Displays Fuel.ppm image
void DrawFuelBox(GLuint fuelBoxTexture, FuelBox *f)
{

    glPushMatrix();
    glTranslatef(f->pos[0], f->pos[1], f->pos[2]);
    glRotatef(f->angle+10, 0.0f, 0.0f, 1.0f);

    // Texture
    glBindTexture(GL_TEXTURE_2D, fuelBoxTexture);
    glBegin(GL_QUADS);
    // Center is 0 so going + and - lets us draw around
    // the center.
    glTexCoord2f(0.0f, 1.0f); glVertex2i(-15,-25);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(-15,25);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(15,25);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(15,-25);
    glEnd();
    glPopMatrix();
    glBegin(GL_POINTS);
    // glVertex2f(a->pos[0], a->pos[1]);
    glEnd();

}

// Initialize the values of the AmoBox struct
void buildAmoBox(AmoBox *a)
{
    a->radius = 35;
    a->angle = 0.0f;
    a->pos[0] = (Flt)(rand() % xres);
    a->pos[1] = (Flt)(rand() % xres);
    a->pos[2] = 0.0f;
    a->angle = 0.0;

    a->rotate = rnd() * 10.0 - 2.0;
    a->vel[0] = (Flt)(rnd()/2);
    a->vel[1] = (Flt)(rnd()/2);    
}

// Display AmoPack.ppm image
void DrawAmoBox(GLuint amoBoxTexture, AmoBox *a){

    glPushMatrix();
    glTranslatef(a->pos[0], a->pos[1], a->pos[2]);
    glRotatef(a->angle+10, 0.0f, 0.0f, 1.0f);

    // Texture
    glBindTexture(GL_TEXTURE_2D, amoBoxTexture);
    glBegin(GL_QUADS);
    // Center is 0 so going + and - lets us draw around
    // the center.
    glTexCoord2f(0.0f, 1.0f); glVertex2i(-15,-20);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(-15,20);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(15,20);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(15,-20);
    glEnd();
    glPopMatrix();
    glBegin(GL_POINTS);
    // glVertex2f(a->pos[0], a->pos[1]);
    glEnd();
}
