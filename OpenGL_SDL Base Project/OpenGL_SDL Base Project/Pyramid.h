#ifndef _PYRAMID_H
#define _PYRAMID_H

#include <Windows.h> //Required for OpenGL on Windows
#include <GL\gl.h>
#include <GL\glu.h>
#include "Commons.h"
#include "../gl/glut.h"

class Pyramid
{
	private:
		Vertex3D * indexedVertices;
		short * indices;
		Colour colours;

		int numNormals;
		Vector3D * normals;

		int numVertices;
		int indexCount;

		bool Load(char* path);
		void DrawTriangle(short a, short b, short c);

	public:
		Pyramid(void);
		~Pyramid(void);

		void Draw(void);
		
		void Update(float deltaTime);
		void Render(float x, float y, float z);
};

#endif