#include "ObjectObj.h"
#include "../gl/glut.h"
#include "ObjLoader.h"

ObjectObj::ObjectObj(Vector3D startPosition, const char* modelFileName, Colour colour, Vector3D startRotation)
{
	//Start position
	mPosition = startPosition;

	//Colour
	mColour = colour;

	//Rotation
	mRotation = startRotation;

	//Obj file to load
	loadModel(modelFileName);

	//Create Loader Ref
	p_objLoad = new ObjLoader();
}

ObjectObj::~ObjectObj()
{
	delete p_objLoad;
}

void ObjectObj::loadModel(const char* modelFileName)
{
	if (modelFileName[0] != '---')
		objInt = p_objLoad->Load(modelFileName);
}

void ObjectObj::Update(float deltaTime)
{
	//Move object here
}

void ObjectObj::Render(Vector3D rotation)
{
	glPushMatrix();
		glTranslatef(mPosition.x, mPosition.y, mPosition.z);
		glColor3f(mColour.r, mColour.g, mColour.b);
		
		rotation.x += mRotation.x;
		rotation.y += mRotation.y;
		rotation.z += mRotation.z;

		glRotatef(rotation.x, 1, 0, 0);
		glRotatef(rotation.y, 0, 1, 0);
		glRotatef(rotation.z, 0, 0, 1);

		glCallList(objInt);
	glPopMatrix();
}

