#ifndef _OBJECT3DS_H_
#define _OBJECT3DS_H_

#include "Commons.h"
#include <string>
using std::string;

class Object3ds
{
public:
	Object3ds(Vector3D startPosition, string modelFileName, Colour colour, Vector3D startRotation, Vector3D startSize);
	~Object3ds(){};

	void		Update(float deltaTime, bool rotate);
	void		Render(Vector3D rotation, Vector3D position);

	//Load 3ds file
	void		loadModel();

	//Load texture for this model
	void		loadTexture();

private:
	Vector3D	mPosition;
	Colour		mColour;
	Vector3D	mRotation;
	Vector3D	mSize;

	char		fileName[20];
	char		textureName[20];

	obj_type	object;
};

#endif