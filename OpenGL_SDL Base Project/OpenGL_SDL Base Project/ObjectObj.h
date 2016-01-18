#ifndef _OBJECTOBJ_H_
#define _OBJECTOBJ_H_

#include "Commons.h"
#include "ObjLoader.h"
#include <string>
using std::string;

class ObjectObj
{
public:
	ObjectObj(Vector3D startPosition, const char* modelFileName, Colour colour, Vector3D startRotation);
	~ObjectObj();

	void	Update(float deltaTime);
	void	Render(Vector3D rotation);

	//Load Obj file
	void	loadModel(const char* modelFileName);

private:
	Vector3D	mPosition;
	Colour		mColour;
	Vector3D	mRotation;

	//char		fileName[20];

	int			objInt;

	ObjLoader*	p_objLoad;
};

#endif