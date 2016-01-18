#include "Object3ds.h"
#include "../gl/glut.h"
#include "3dsLoader.h"

Object3ds::Object3ds(Vector3D startPosition, string modelFileName, Colour colour, Vector3D startRotation, Vector3D startSize)
{
	//Start position.
	mPosition = startPosition;

	//Start colour.
	mColour = colour;

	//Start rotation.
	mRotation = startRotation;

	//Start Size.
	mSize = startSize;

	//3ds file to load.
	strcpy(fileName, modelFileName.c_str());
	loadModel();
}

void Object3ds::loadModel()
{
	//Load model
	if (fileName[0] != '-нн')
		Load3DS(&object, fileName);
}

void Object3ds::loadTexture()
{
	//Load a texture to map to the object.
}

void Object3ds::Update(float deltaTime, bool rotate)
{
	//TODO: Move object here.
	if (rotate)
		mRotation.z -= deltaTime;
}

void Object3ds::Render(Vector3D rotation, Vector3D position)
{
	glPushMatrix();

	//Scale object
	glScalef(mSize.x, mSize.y, mSize.z);

	//Reset to (0.0, 0.0, 0.0)
	glTranslatef(mPosition.x - mPosition.x, mPosition.y - mPosition.y, mPosition.z - mPosition.z);

	//Rotate
	rotation.x += mRotation.x;
	rotation.y += mRotation.y;
	rotation.z += mRotation.z;

	glRotatef(rotation.x, 1, 0, 0);
	glRotatef(rotation.y, 0, 1, 0);
	glRotatef(rotation.z, 0, 0, 1);

	//Move to new location
	glTranslatef(mPosition.x + position.x, mPosition.y, mPosition.z + position.z);

	// We set the active texture
	//glBindTexture(GL_TEXTURE_2D, object.id_texture); 

	//glBegin and glEnd delimit the vertices that define a primitive(in our case triangles)
	glBegin(GL_TRIANGLES);
	
	for (int l_index = 0; l_index < object.triangles_qty; l_index++)
	{
		//-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн FIRST VERTEX -нн-нн-
		// Texture coordinates of the first vertex
		//glTexCoord2f(object.texcoord[object.triangle[l_index].a].u, object.texcoord[object.triangle[l_index].a].v); 

		//Coordinates of the first vertex
		glVertex3f(object.vertex[object.triangle[l_index].a].x, object.vertex[object.triangle[l_index].a].y, object.vertex[object.triangle[l_index].a].z);

		//Colour for first vertex
		glColor3f(mColour.r, mColour.g, mColour.b);

		//-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн SECOND VERTEX -нн-нн-
		// Texture coordinates of the second vertex
		//glTexCoord2f(object.texcoord[object.triangle[l_index].b].u, object.texcoord[object.triangle[l_index].b].v);

		// Coordinates of the second vertex
		glVertex3f(object.vertex[object.triangle[l_index].b].x, object.vertex[object.triangle[l_index].b].y, object.vertex[object.triangle[l_index].b].z);

		//Colour for second vertex
		glColor3f(mColour.r, mColour.g, mColour.b);
		//-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн THIRD VERTEX -нн-нн-
		// Texture coordinates of the third vertex
		//glTexCoord2f( object.texcoord[ object.triangle[l_index].c ].u, object.texcoord[ object.triangle[l_index].c ].v);

		// Coordinates of the Third vertex
		glVertex3f(object.vertex[object.triangle[l_index].c].x, object.vertex[object.triangle[l_index].c].y, object.vertex[object.triangle[l_index].c].z);

		//Colour for Third vertex
		glColor3f(mColour.r, mColour.g, mColour.b);
	}

	glEnd();
	glPopMatrix();
}
//-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн