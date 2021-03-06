#include "Pyramid.h"
#include <fstream>
#include <iostream>

using namespace::std;

Pyramid::Pyramid()
{
	Load("Pyramid.txt");

	colours = Colour(1.0f, 0.0f, 0.0f);
}

//--------------------------------------------------------------------------------------------------

Pyramid::~Pyramid()
{
	delete indexedVertices;
	delete indices;

	delete normals;
}

//--------------------------------------------------------------------------------------------------

void Pyramid::Update(float deltaTime)
{
}

//--------------------------------------------------------------------------------------------------

void Pyramid::Render(float x, float y, float z)
{
	glPushMatrix();
		glRotatef(x, 1, 0, 0);
		glRotatef(y, 0, 1, 0);
		glRotatef(z, 0, 0, 1);
		glColor3f(colours.r, colours.g, colours.b);
		Draw();
	glPopMatrix();
}

//--------------------------------------------------------------------------------------------------

bool Pyramid::Load(char* path)
{
	ifstream inFile;
	inFile.open(path);

	if (!inFile.good())
	{
		cerr << "Can't open model file " << path << endl;
		return false;
	}

	inFile >> numVertices;

	if (numVertices > 0)
	{
		indexedVertices = new Vertex3D[numVertices];
		for (int i = 0; i < numVertices; i++)
		{
			inFile >> indexedVertices[i].x;
			inFile >> indexedVertices[i].y;
			inFile >> indexedVertices[i].z;
		}
	}

	inFile >> numNormals;

	if (numNormals > 0)
	{
		normals = new Vector3D[numNormals];
		for (int i = 0; i < numNormals; i++)
		{
			inFile >> normals[i].x;
			inFile >> normals[i].y;
			inFile >> normals[i].z;
		}
	}

	int numTriangles;
	inFile >> numTriangles;
	indexCount = numTriangles * 3;

	if (indexCount > 0)
	{
		indices = new short[indexCount];
		for (int i = 0; i < indexCount; i++)
		{
			inFile >> indices[i];
		}
		inFile.close();
		return true;
	}
}

//--------------------------------------------------------------------------------------------------

void Pyramid::Draw()
{
	for (int i = 0; i < indexCount; i += 3)
	{
		DrawTriangle(indices[i], indices[i + 1], indices[i + 2]);
	}
}

//--------------------------------------------------------------------------------------------------

void Pyramid::DrawTriangle(short a, short b, short c)
{
	glBegin(GL_TRIANGLES);	

	glColor3f(1.0f, 0.0f, 0.0f);
	glNormal3f(normals[a].x, normals[a].y, normals[a].z);
	glVertex3f(indexedVertices[a].x, indexedVertices[a].y, indexedVertices[a].z);

	glColor3f(1.0f, 0.0f, 0.0f);
	glNormal3f(normals[b].x, normals[b].y, normals[b].z);
	glVertex3f(indexedVertices[b].x, indexedVertices[b].y, indexedVertices[b].z);
	
	glColor3f(1.0f, 0.0f, 0.0f);
	glNormal3f(normals[c].x, normals[c].y, normals[c].z);
	glVertex3f(indexedVertices[c].x, indexedVertices[c].y, indexedVertices[c].z);

	glEnd();
}