#include "GameScreenLevel1.h"
#include "Lighting.h"
#include <time.h>
#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "../gl/glut.h"
#include "Constants.h"
#include "Commons.h"
#include <iostream>
#include "ObjLoader.h"

using namespace::std;

//--------------------------------------------------------------------------------------------------

GameScreenLevel1::GameScreenLevel1() : GameScreen()
{
	zero = Vector3D(0.0f, 0.0f, 0.0f);

	rotation = zero;

	srand(time(NULL));

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	gluPerspective(20.0f, aspect, 1.0f, 200.0f);

	glMatrixMode(GL_MODELVIEW);

	//Stop calculation of inside faces
	glEnable(GL_CULL_FACE);	

	//Hidden surface removal
	glEnable(GL_DEPTH_TEST);

	//Show faces
	glCullFace(GL_BACK);

	//Set Color Material
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	
	//Enable Color Material
	glEnable(GL_COLOR_MATERIAL);

	//clear background colour.
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	m_pClockBase = new Object3ds	(Vector3D(0.0f, 0.0f, -3.0f),	"ClockBase.3ds",	Colour(1.0f, 0.0f, 0.0f),		Vector3D(0.0f, 0.0f, 180.0f),	Vector3D(1.0f, 1.0f, 1.0f));
	m_pNumbers = new Object3ds		(Vector3D(0.0f, 10.0f, 0.5f),	"Numbers.3ds",		Colour(0.0f, 1.0f, 0.0f),		zero,							Vector3D(1.05f, 1.05f, 1.05f));
	m_pMinHand = new Object3ds		(Vector3D(0.0f, 0.0f, 1.0f),	"MinuteHand.3ds",	Colour(0.0f, 0.0f, 1.0f),		zero,							Vector3D(1.0f, 1.0f, 1.0f));
	m_pSecHand = new Object3ds		(Vector3D(0.0f, 0.0f, 2.0f),	"SecondHand.3ds",	Colour(1.0f, 1.0f, 0.0f),		zero,							Vector3D(1.0f, 0.85f, 1.0f));
	m_pHourHand = new Object3ds		(zero,							"HourHand.3ds",		Colour(1.0f, 0.0f, 1.0f),		zero,							Vector3D(1.0f, 1.0f, 1.0f));

	loaderRef = new ObjLoader();
	cube = loaderRef->Load("TestCube.obj");

	textRef = new TextDisplay();

	//enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//Set light
	lighting = new Lighting;
	lighting->SetLight(2);

	//Scaling used
	glEnable(GL_NORMALIZE);

	//Set start speed
	mSpeed = 1;

	//Set unpaused
	mPaused = false;
}

//--------------------------------------------------------------------------------------------------

GameScreenLevel1::~GameScreenLevel1()
{
	delete	m_pClockBase;
	delete	m_pNumbers;
	delete	m_pMinHand;
	delete	m_pSecHand;
	delete	m_pHourHand;

	delete	textRef;
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::Render()
{
	//Clear the screen.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
		gluLookAt(0.0, 0.0, 100.0f,
				  0.0, 0.0, 0.0,
				  0.0, 1.0, 0.0);

	//Render Lighting
	lighting->Render();

	//Remder models
	m_pClockBase->Render(rotation, position);
	m_pNumbers->Render(rotation, position);
	m_pMinHand->Render(rotation, position);
	m_pSecHand->Render(rotation, position);
	m_pHourHand->Render(rotation, position);

	glPushMatrix();
		glScalef(0.1f, 0.1f, 0.1f);
		glTranslatef(200.0f, 0.0f, 0.0f);
		glRotatef(rotation.x, 1, 0, 0);
		glRotatef(rotation.y, 0, 1, 0);
		glRotatef(rotation.z, 0, 0, 1);
		glCallList(cube);
	glPopMatrix();

	//Render text
	textRef->Render(mSpeed);
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	//Set current time
	mCurrentTime += deltaTime;

	//Check for input
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_w:
				position.z -= 0.5f;
			break;

			case SDLK_s:
				position.z += 0.5f;
			break;

			case SDLK_a:
				rotation.z += 1.5f;
			break;

			case SDLK_d:
				rotation.z -= 1.5f;
			break;

			case SDLK_q:
				rotation.y += 1.5f;
			break;

			case SDLK_e:
				rotation.y -= 1.5f;
			break;

			case SDLK_LEFT:
				if (mSpeed > -9999)
					mSpeed -= 1000;
			break;

			case SDLK_RIGHT:
				if (mSpeed < 10001)
					mSpeed += 1000;
			break;

			case SDLK_r:
				mSpeed = 1;
			break;

			case SDLK_SPACE:
				if (mPaused)
					mPaused = false;
				else
					mPaused = true;
			break;
		}
	}

	//Update models if not paused
	if (!mPaused)
	{
		m_pClockBase->Update(deltaTime, false);
		m_pNumbers->Update(deltaTime, false);

		m_pSecHand->Update((deltaTime * 6) * mSpeed, true);
		m_pMinHand->Update((deltaTime * 6 / 60) * mSpeed, true);
		m_pHourHand->Update((deltaTime * 6 / 60 / 60) * mSpeed, true);
	}

	//Update text
	textRef->Update(mPaused);
}

//--------------------------------------------------------------------------------------------------