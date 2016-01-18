#include <windows.h>
#include "../gl/glut.h"
#include <stdio.h> 
#include "TextDisplay.h"
#include "Constants.h"

TextDisplay::TextDisplay()
{
}

TextDisplay::~TextDisplay()
{
}

void TextDisplay::SetOrthographicProjection() 
{
	//Sets up where to render on screen
	glMatrixMode(GL_PROJECTION);

	glPushMatrix();
	glLoadIdentity();

	//Sets screen size
	gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
	
	//Adjusts scale and transform
	glScalef(1, -1, 1);
	glTranslatef(0, -SCREEN_HEIGHT, 0);

	glMatrixMode(GL_MODELVIEW);
}
void TextDisplay::ResetPerspectiveProjection() 
{
	//Resets normal view
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void TextDisplay::RenderBitmapString(float x, float y, void *font, string text)
{
	glRasterPos2f(x, y);
	
	for (int i = 0; i < text.size(); i++)
	{
		glutBitmapCharacter(font, text[i]);
	}
}

void TextDisplay::Render(int speed)
{
	SetOrthographicProjection();

	//Converts speed to const char
	speedString = to_string(speed);
	speedString += "x";

	glLoadIdentity();
		//Sets colour
		glColor3d(0.0, 0.0, 0.0);

		//Renders text
		RenderBitmapString(20, 20, GLUT_BITMAP_HELVETICA_18, "Current Speed: ");
		RenderBitmapString(150, 20, GLUT_BITMAP_HELVETICA_18, speedString);

		//Checks to see if paused before rendering
		if (mPaused)
			RenderBitmapString(20, 40, GLUT_BITMAP_HELVETICA_18, "PAUSED");

	ResetPerspectiveProjection();
}

void TextDisplay::Update(bool paused)
{
	//Checks to see if paused
	if (mPaused != paused)
		mPaused = paused;
}