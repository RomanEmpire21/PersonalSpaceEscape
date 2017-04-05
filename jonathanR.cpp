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
    while(a){
	d2 = g->astronaut.pos[0] - a->pos[0];
	d3 = g->astronaut.pos[1] - a->pos[1];
	dist2 = (d2*d2 + d3*d3);
	if (dist2 < (a->radius*2)*(a->radius*2)) {
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
    glColor3f(0.0,0.0,0.0);
    float cx = x;
    int cy = y;
    glBegin(GL_QUADS);
    glVertex2i(cx-155,cy+15);
    glVertex2i(cx+155,cy+15);
    glVertex2i(cx+155,cy-15);
    glVertex2i(cx-155,cy-15);
    glEnd();
    glEnable(GL_TEXTURE_2D);
    glColor3f(0.0,1.0,0.0);
    if (fuel <= 50) {
	glColor3f(1.0,0.0,0.0);
    }

    glBegin(GL_QUADS);
    glVertex2i(cx-150,cy+10);

    // Setting up location of box
    glVertex2i(cx+fuelView-150,cy+10);
    glVertex2i(cx+fuelView-150,cy-10);
    glVertex2i(cx-150,cy-10);
    glEnd();
    r.bot = cy -5;
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
    fuel = fuel - .2;
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
int reduceAmo(int bulletsRemain){
    return --bulletsRemain;
}

void getHealthPack(Game *g, HealthBox *healthbox, int &health)
{
    // Attempt to detect collision between asteroid and
    // astronaut
    Flt d2, d3, dist2;
    d2 = g->astronaut.pos[0] - healthbox->pos[0];
    d3 = g->astronaut.pos[1] - healthbox->pos[1];
    dist2 = (d2*d2 + d3*d3);
    if (dist2 < healthbox->radius*healthbox->radius) {
	// You can come into the radius of the healthbox
	health += 50;
    }
}

