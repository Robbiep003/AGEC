#include "Lighting.h"
#include <time.h>
#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "../gl/glut.h"
#include "Commons.h"


//--------------------------------------------------------------------------------------------------

Lighting::Lighting()
{
}

//--------------------------------------------------------------------------------------------------

Lighting::~Lighting()
{
}

//--------------------------------------------------------------------------------------------------

void Lighting::Render()
{
}

//--------------------------------------------------------------------------------------------------

void Lighting::SetLight(int colour)
{
	light light;

	switch (colour)
	{
	default:
	case 0:
		light = RedLight();
		break;

	case 1:
		light = BlueLight();
		break;

	case 2:
		light = WhiteLight();
		break;
	}

	// Position of the light in homogenwous coordinates (x, y, z, w)
	// w should be 0 for directional lights, and 1 for spotlights

	float light_pos[] = { 1.0f, 1.0f, 1.0f, 0.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light.ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light.diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light.specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}

//--------------------------------------------------------------------------------------------------

light Lighting::RedLight()
{
	return{
		{ 0.2f, 0.2f, 0.2f, 1.0f },
		{ 0.7f, 0.7f, 0.7f, 1.0f },
		{ 0.5f, 0.5f, 0.5f, 1.0f }
	};
}

//--------------------------------------------------------------------------------------------------

light Lighting::BlueLight()
{
	return{
		{ 0.0, 0.0, 0.5, 1.0 },
		{ 0.0, 0.0, 0.5, 1.0 },
		{ 0.0, 0.0, 0.5, 1.0 }
	};
}

//--------------------------------------------------------------------------------------------------

light Lighting::WhiteLight()
{
	return{
		{ 1.0, 1.0, 1.0, 1.0 },
		{ 1.0, 1.0, 1.0, 1.0 },
		{ 1.0, 1.0, 1.0, 1.0 }
	};
}

//--------------------------------------------------------------------------------------------------