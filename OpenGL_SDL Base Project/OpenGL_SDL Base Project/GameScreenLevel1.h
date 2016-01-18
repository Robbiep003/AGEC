#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include <SDL.h>
#include "GameScreen.h"
#include "Pyramid.h"
#include "Lighting.h"
#include "Object3ds.h"
#include "ObjectObj.h"
#include "ObjLoader.h"
#include "TextDisplay.h"

class GameScreenLevel1 : GameScreen
{
//--------------------------------------------------------------------------------------------------
public:
	GameScreenLevel1();
	~GameScreenLevel1();

	bool		SetUpLevel();
	void		Render();
	void		Update(float deltaTime, SDL_Event e);

//--------------------------------------------------------------------------------------------------
private:
	
	float			mCurrentTime;
	
	//Pyramid*		pyramid;
	
	Lighting*		lighting;

	int				cube;
	ObjLoader*		loaderRef;

	//Object3ds*		m_p3dsModel;

	//ObjectObj*		m_pObjModel;
	//int				testObj;

	Object3ds*		m_pClockBase;
	Object3ds*		m_pNumbers;
	Object3ds*		m_pMinHand;
	Object3ds*		m_pSecHand;
	Object3ds*		m_pHourHand;

	Vector3D		rotation;
	Vector3D		position;

	Vector3D		zero;

	int				mSpeed;

	TextDisplay*	textRef;

	bool			mPaused;
};

#endif //_GAMESCREENLEVEL1_H