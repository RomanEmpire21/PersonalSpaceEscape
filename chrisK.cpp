//Author: Chris Kelly
//Purpose: SPACE Escape personal file 
//Date - 3-2-17
//CS 3350 

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <ctime>
#include <cmath>
#include <X11/Xlib.h>
//#include <X11/Xutil.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "log.h"
#include "fonts.h"
#include "ppm.h"
#include "typedefine.h"



void healthbar(int x, int y, Rect r, int &health) 
{
    int healthView = health;
    // glDisable(GL_TEXTURE_2D);
    glColor3f(0.0,0.0,0.0);
    int cx = x;
    int cy = y;
    glBegin(GL_QUADS);
    glVertex2i(cx-155,cy+15);
    glVertex2i(cx+155,cy+15);
    glVertex2i(cx+155,cy-15);
    glVertex2i(cx-155,cy-15);
    glEnd(); 
    glEnable(GL_TEXTURE_2D);
    glColor3f(0.0,1.0,0.0);
    if (healthView <= 20) {
	glColor3f(1.0,0.0,0.0);
    }

    glBegin(GL_QUADS);
    glVertex2i(cx-150,cy+10);
    glVertex2i(cx+healthView-150,cy+10);
    glVertex2i(cx+healthView-150,cy-10);
    glVertex2i(cx-150,cy-10);
    glEnd(); 
    r.bot = cy -5;
    r.left = cx ;
    r.center = 1;
    //glEnable(GL_TEXTURE_2D);		If you want to see amount
    ggprint8b(&r,20,0x00ffffff, "Health");// %d", health);
    glEnable(GL_TEXTURE_2D);

}

void buildHealthBox(HealthBox *h) {
    h->radius = 37;
    h->angle = 0.0f;
    h->pos[0] = (Flt)(rand() % xres);
    h->pos[1] = (Flt)(rand() % xres);
    h->pos[2] = 0.0f;
    h->angle = 0.0;

    h->rotate = rnd() * 10.0 - 2.0;
    // Commented for testing purposes. 
    // Uncomment when done fixing healthbox issue.
    h->vel[0] = (Flt)(rnd()/2);
    h->vel[1] = (Flt)(rnd()/2);

}


// Function used to draw health box and update the position
// so that it "floats" in space.


void DrawHealthBox(GLuint healthBoxTexture, HealthBox *h) {

    glPushMatrix();
    glTranslatef(h->pos[0], h->pos[1], h->pos[2]);
    glRotatef(h->angle+10, 0.0f, 0.0f, 1.0f);


    // Texture

    glBindTexture(GL_TEXTURE_2D, healthBoxTexture);
    glBegin(GL_QUADS);
    // The 20's are used to draw around the center.
    // Center is 0 so going + and - lets us draw around
    // the center.
    glTexCoord2f(0.0f, 1.0f); glVertex2i(-12,-20);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(-12,20);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(12,20);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(12,-20);
    glEnd();
    glPopMatrix();
    glBegin(GL_POINTS);

    // glVertex2f(a->pos[0], a->pos[1]);

    glEnd();
}

unsigned char *buildAlphaData(Ppmimage *img)
{
        //add 4th component to RGB stream...
        int i;
        int a,b,c;
        unsigned char *newdata, *ptr;
        unsigned char *data = (unsigned char *)img->data;
        newdata = (unsigned char *)malloc(img->width * img->height * 4);
        ptr = newdata;
        for (i=0; i<img->width * img->height * 3; i+=3) {
                a = *(data+0);
                b = *(data+1);
                c = *(data+2);
                *(ptr+0) = a;
                *(ptr+1) = b;
                *(ptr+2) = c;
                //get largest color component...
                //*(ptr+3) = (unsigned char)((
                //              (int)*(ptr+0) +
                //              (int)*(ptr+1) +
                //              (int)*(ptr+2)) / 3);
                //d = a;
                //if (b >= a && b >= c) d = b;
                //if (c >= a && c >= b) d = c;
                //*(ptr+3) = d;
                *(ptr+3) = (a|b|c);
                ptr += 4;
                data += 3;
        }
        return newdata;
}
