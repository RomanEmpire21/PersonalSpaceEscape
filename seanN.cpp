//Author: Sean Nickell
//Purpose of file: Keypresses, and soon to be rendering
//Date Modified: 3/2/17

#include <GL/glx.h>
#include </usr/include/AL/alut.h>
#include "ppm.h"

extern int xres, yres;

void changeBackground(int background, GLuint Level1Texture, GLuint Level2Texture, 
	GLuint Level3Texture, GLuint Level4Texture, GLuint Level5Texture)
{
    if (background ==1) {
	glBindTexture(GL_TEXTURE_2D, Level1Texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(0,0);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(0,yres);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(xres,yres);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(xres,0);
	glEnd();
    }

    if (background ==2) {
	glBindTexture(GL_TEXTURE_2D, Level2Texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(0,0);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(0,yres);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(xres,yres);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(xres,0);
	glEnd();
    }

    if (background ==3) {
	glBindTexture(GL_TEXTURE_2D, Level3Texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(0,0);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(0,yres);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(xres,yres);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(xres,0);
	glEnd();
    }

    if (background ==4) {
	glBindTexture(GL_TEXTURE_2D, Level4Texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(0,0);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(0,yres);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(xres,yres);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(xres,0);
	glEnd();
    }

    if (background ==5) {
	glBindTexture(GL_TEXTURE_2D, Level5Texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(0,0);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(0,yres);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(xres,yres);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(xres,0);
	glEnd();
    }
}

void getAudio(int num, ALuint* alSource)
{
    if (num == 0) {
	alSourceStop(alSource[0]);
	alSourcePlay(alSource[0]);
    }
    else {
	alSourceStopv(8, alSource);
	for (int i=1; i<8; i++) {
	    if (num == i) 
		alSourcePlay(alSource[i]);
	}	
    }
}

