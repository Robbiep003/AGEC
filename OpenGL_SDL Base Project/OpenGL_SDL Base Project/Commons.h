#pragma once

#include <iostream>
using namespace::std;

enum SCREENS
{
	SCREEN_INTRO = 0,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES
};

struct Rect2D
{
	float x;
	float y;
	float width;
	float height;

	Rect2D(float initialX, float initialY, float initialWidth, float initialHeight)
	{
		x = initialX;
		y = initialY;
		width  = initialWidth;
		height = initialHeight;
	}
};

struct Vector2D
{
	float x;
	float y;

	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2D(float initialX, float initialY)
	{
		x = initialX;
		y = initialY;
	}
};

struct Vector3D
{
	float x;
	float y;
	float z;

	Vector3D()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	Vector3D(float initialX, float initialY, float initialZ)
	{
		x = initialX;
		y = initialY;
		z = initialZ;
	}
};

struct Vertex3D
{
	float x;
	float y;
	float z;
};


struct Colour
{
	float r;
	float g;
	float b;

	Colour()
	{
		r = 0.0f;
		g = 0.0f;
		b = 0.0f;
	}

	Colour(float initialR, float initialG, float initialB)
	{
		r = initialR;
		g = initialG;
		b = initialB;
	}
};

struct light
{
	float ambient[4];
	float diffuse[4];
	float specular[4];
};

struct material
{
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float shininess;
};

#define MAX_VERTICES 15000
#define MAX_POLYGONS 15000

struct Triangle
{
	int a, b, c;
};

struct TexCoord
{
	TexCoord(){};
	~TexCoord(){};

	int u, v;
	TexCoord(float a, float b);
};

typedef struct obj_type
{
	obj_type(){};
	~obj_type(){};

	char		name[20];

	int			vertices_qty, polygons_qty, triangles_qty;

	Vertex3D	vertex[MAX_VERTICES];

	//Triangle	polygon[MAX_POLYGONS];

	Triangle	triangle[MAX_POLYGONS];

	//TexCoord	mapcoord[MAX_VERTICES];

	TexCoord	TexCoord[MAX_VERTICES];

	int			id_texture;

}	obj_type, *obj_type_ptr;


struct face
{
	int facenum;			//The number of the face for the normal vectors
	bool four;              //If true than it's a quad, else it's a triangle
	int faces[4];			//Indexes for every vertex, which makes the face
	int texcoord[4];        //Indexes for every texture coorinate that is in the face
	int mat;                //The index for the material
	face(int facen, int f1, int f2, int f3, int t1, int t2, int t3, int m);					//Constuctor for triangle
	face(int facen, int f1, int f2, int f3, int f4, int t1, int t2, int t3, int t4, int m); //-"- for quad
};

//This contains one material
struct materialObj
{
	string name;					//The name of the material
	float alpha, ns, ni;			//Not used
	float dif[3], amb[3], spec[3];  //The color property (diffuse, ambient, specular)
	int illum;						//Not used
	int texture;					//The id for the texture, if there is no texture than -1
	materialObj(const char* na, float al, float n, float ni2, float* d, float* a, float* s, int i, int t);
};

struct texcoordObj
{
	float u, v;
	texcoordObj(float a, float b);
};