#include "Texture2D.h"
#include <iostream>
#include <fstream>

using namespace::std;

Texture2D::Texture2D()
{
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &_ID);
}

bool Texture2D::Load(char* path, int width, int height)
{
	char* tempTextureData; int fileSize; ifstream inFile;
	_width = width; _height = height;
	inFile.open(path, ios::binary);

	if (!inFile.good())
	{
		cerr << "Can't open texture file " << path << endl;
		return false;
	}

	//Seek to end of file
	inFile.seekg(0, ios::end);

	//Get current position in file - The End, this gives us total file size
	fileSize = (int)inFile.tellg();

	//Create an new array to store data
	tempTextureData = new char[fileSize];

	//Seek back to beginning of file
	inFile.seekg(0, ios::beg);

	//Read in all the data in one go
	inFile.read(tempTextureData, fileSize);

	//Close the file
	inFile.close();

	cout << path << " loaded." << endl;

	//Get next Texture ID
	glGenTextures(1, &_ID);

	//Bind the texture to the ID
	glBindTexture(GL_TEXTURE_2D, _ID);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);

	//Clear up the data - we don't need this any more
	delete[] tempTextureData;
	return true;
}