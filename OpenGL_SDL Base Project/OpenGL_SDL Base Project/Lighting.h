#ifndef _LIGHTING_H
#define _LIGHTING_H

#include <SDL.h>
#include "Commons.h"

class Lighting
{
public:
	Lighting();
	~Lighting();

	void	 SetLight(int colour);

	light	RedLight();
	light	BlueLight();
	light	WhiteLight();

	virtual void	Render();

protected:

};

#endif //_LIGHTING_H