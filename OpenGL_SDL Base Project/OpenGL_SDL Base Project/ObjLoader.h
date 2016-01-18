#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <iostream>
#include "Commons.h"

#ifndef OBJLOADER_H
#define OBJLOADER_H

using namespace::std;

class ObjLoader
{
public:
	ObjLoader();
	~ObjLoader();

	int Load(const char* filename);

private:
	vector<string*>			coord;								//Every line of code from the obj file
	vector<Vector3D*>		vertex;								//All vertexes
	vector<face*>			faces;								//All faces
	vector<Vector3D*>		normals;							//All normal vectors
	vector<unsigned int>	texture;							//The id for all the textures (used for deleting the textures after use it)
	vector<unsigned int>	lists;								//The id for all lists (used for deleting the lists after use it)
	vector<materialObj*>	materials;							//All materials
	vector<texcoordObj*>	texturecoordinate;					//All texture coorinates (UV coordinate)
	bool					ismaterial;
	bool					isnormals;
	bool					istexture;							//Check to see what it is
	unsigned int			loadTexture(const char* filename);	//Load texture function
	void					clean();							//Free all of the used memory
	int						curmat;								//The current (default) material is 0, it's used, when reading the faces
	
	Vector3D				mPosition;

	int						objInt;
};

#endif