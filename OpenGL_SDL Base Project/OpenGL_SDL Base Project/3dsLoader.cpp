#include <stdio.h>
#include <stdlib.h>
#include "Commons.h"
#include "3dsLoader.h"
#include <sys\stat.h>

//-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-н----------- нн

long fileLength(int f)
{
	struct stat buf;
	fstat(f, &buf);
	return(buf.st_size);
}

//-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-нн-н-----------

char Load3DS(obj_type_ptr p_object, char *p_filename)
{
	//Index variable
	int i;
	
	//File Pointer
	FILE *inFile;

	//Chunk identifier unsigned
	unsigned short chunkId, s_temp;

	//Chunk length
	int chunkLength;

	//Char variable
	unsigned char name;

	//Number of elements in each chunk
	unsigned short size;

	//Flag that stores some face infomation
	unsigned short faceFlag;

	//Open the file
	if ((inFile = fopen(p_filename, "rb")) == NULL)
		return 0;

	//Loop to scan the whole file
	while (ftell(inFile) < fileLength(fileno(inFile)))
	{
		//Read the chunk header
		fread(&chunkId, 2, 1, inFile);

		//Read the length of the chunk
		fread(&chunkLength, 4, 1, inFile);

		//Insert this command for debug (to wait for keypress for each chunk reading)
		//getchar();

		switch (chunkId)
		{
			//----------MAIN3DS---------
			//Description: Main chunk, contains all the other chunks
			//Chunk IDL 4d4d#
			//Chunk Length: 0 + sub chunks

			case 0x4d4d:
			break;

			//--------------------------

			//----------EDIT3DS---------
			//Description: 3D Editior chunk, objects layout info
			//Chunk ID: 3d3d (hex)
			//Chunk Length: 0 + sub chunks

			case 0x3d3d:
			break;

			//--------------------------
			
			//--------EDIT_OBJECT-------
			//Description: Object block, info for each object
			//Chunk ID: 4000 (hex)
			//Chunk Length: len(object name) + sub chunks

			case 0x4000:
				i = 0;
				do
				{
					fread(&name, 1, 1, inFile);
					p_object->name[i] = name;
					i++;
				} while (name != '\0' && i < 20);
			break;

			//--------------------------

			//-------OBJ_TRIMESH--------
			//Description: Triangluar mesh, contatins chunks for 3d mesh info
			//Chunk ID: 4100 (hex)
			//Chunk Length: 0 + sub chunks

			case 0x4100:
			break;

			//--------------------------

			//--------TRI_VERTEXL--------
			//Description: Vertices list
			//Chunk ID: 4110 (hex)
			//Chunk Length: 1 x unsinged short (number of vertices) + 3 x float (vertex coordinates) x (number of vertices) + sub chunks

			case 0x4110:
				fread(&size, sizeof(unsigned short), 1, inFile);
				p_object->vertices_qty = size;

				for (i = 0; i < size; i++)
				{
					fread(&p_object->vertex[i].x, sizeof(float), 1, inFile);
					fread(&p_object->vertex[i].y, sizeof(float), 1, inFile);
					fread(&p_object->vertex[i].z, sizeof(float), 1, inFile);
				}
			break;
			
			//--------------------------

			//--------TRI_FACEL1--------
			//Description: Triangles (faces) list
			//Chunk ID: 4120 (hex)
			//Chunk Length: 1 x unsigned short (number of triangles) + 3 x unsigned short (triangle points) x (number of triangles) + sub chunks

			case 0x4120:
				fread(&size, sizeof(unsigned short), 1, inFile);
				p_object->triangles_qty = size;

				for (i = 0; i < size; i++)
				{
					fread(&s_temp, sizeof(unsigned short), 1, inFile);
					p_object->triangle[i].a = s_temp;

					fread(&s_temp, sizeof(unsigned short), 1, inFile);
					p_object->triangle[i].b = s_temp;

					fread(&s_temp, sizeof(unsigned short), 1, inFile);
					p_object->triangle[i].c = s_temp;

					fread(&faceFlag, sizeof(unsigned short), 1, inFile);
				}
			break;

			//--------------------------

			//-----TRI_MAPPINGCOORS-----
			//Description: Vertices list
			//Chunk ID: 4140 (hex)
			//Chunk Length: 1 x unsigned short (number of mapping points) + 2 x float (mapping coordinates) x (number of mapping points) + sub chunks

			case 0x4140:
				fread(&size, sizeof(unsigned short), 1, inFile);

				for (i = 0; i < size; i++)
				{
					fread(&p_object->TexCoord[i].u, sizeof(float), 1, inFile);

					fread(&p_object->TexCoord[i].v, sizeof(float), 1, inFile);
				}
			break;

			//--------------------------

			//---Skip Unknown Chunks----
			//We need to skip all the chunks that currently we don't use
			//We use the chunk length information to set the file pointer to the same level next chunk

			default:
				fseek(inFile, chunkLength - 6, SEEK_CUR);
		}
	}

	//Close the file
	fclose(inFile);
	return(1);
}