#ifndef _TEXTDISPLAY_H
#define _TEXTDISPLAY_H

#include <iostream>
#include <string>

using namespace::std;

class TextDisplay
{
private:

	//Checks if paused
	bool		mPaused;

	//Converts int to string
	string		speedString;

public:
	TextDisplay();
	~TextDisplay();

	void Render(int speed);
	void Update(bool paused);

	void RenderBitmapString(float x, float y, void *font, string text);

	void ResetPerspectiveProjection();
	void SetOrthographicProjection();
};
#endif