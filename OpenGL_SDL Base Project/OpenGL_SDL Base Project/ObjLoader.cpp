#include "ObjLoader.h"

face::face(int facen, int f1, int f2, int f3, int t1, int t2, int t3, int m)
{
	facenum = facen;
	faces[0] = f1;
	faces[1] = f2;
	faces[2] = f3;
	texcoord[0] = t1;
	texcoord[1] = t2;
	texcoord[2] = t3;
	mat = m;
	four = false;
}

face::face(int facen, int f1, int f2, int f3, int f4, int t1, int t2, int t3, int t4, int m)
{
	facenum = facen;
	faces[0] = f1;
	faces[1] = f2;
	faces[2] = f3;
	faces[3] = f4;
	texcoord[0] = t1;
	texcoord[1] = t2;
	texcoord[2] = t3;
	texcoord[3] = t4;
	mat = m;
	four = true;
}


materialObj::materialObj(const char* na, float al, float n, float ni2, float* d, float* a, float* s, int i, int t)
{
	name = na;
	alpha = al;
	ni = ni2;
	ns = n;
	dif[0] = d[0];
	dif[1] = d[1];
	dif[2] = d[2];

	amb[0] = a[0];
	amb[1] = a[1];
	amb[2] = a[2];

	spec[0] = s[0];
	spec[1] = s[1];
	spec[2] = s[2];

	illum = i;
	texture = t;
}

texcoordObj::texcoordObj(float a, float b)
{
	u = a;
	v = b;
}

ObjLoader::ObjLoader()
{
	//Set all booleans to false
	ismaterial = false;
	isnormals = false;
	istexture = false;

	curmat = 0;
}

ObjLoader::~ObjLoader()
{
	//Delete lists and textures
	for (vector<unsigned int>::const_iterator it = texture.begin(); it != texture.end(); it++)
	{
		glDeleteTextures(1, &(*it));
	}

	for (vector<unsigned int>::const_iterator it = lists.begin(); it != lists.end(); it++)
	{
		glDeleteLists(*it, 1);
	}
}

int ObjLoader::Load(const char* fileName)
{
	//Open the model file
	ifstream in(fileName);

	//Temp buffer
	char buf[256];							

	if (!in.is_open())
	{
		//If it didn't load
		cout << "Not opened" << endl; 
		return -1;
	}

	while (!in.eof())
	{
		//While we are not at the end of the file, read everything as a string to the coord vector
		in.getline(buf, 256);
		coord.push_back(new string(buf));
	}

	//Go through the line and decide what kind of line it is
	for (int i = 0; i < coord.size(); i++) 
	{
		//If it's a comment
		if ((*coord[i])[0] == '#')
		{
			//We don't have to do anything with it
			continue;       
		}
		//If it's a vertex
		else if ((*coord[i])[0] == 'v' && (*coord[i])[1] == ' ')     
		{
			float tmpx, tmpy, tmpz;

			//Read the 3 floats, which makes up the vertex
			sscanf(coord[i]->c_str(), "v %f %f %f", &tmpx, &tmpy, &tmpz); 

			//And put it in the vertex vector
			vertex.push_back(new Vector3D(tmpx, tmpy, tmpz));      
		}
		//If it's a normal vector
		else if ((*coord[i])[0] == 'v' && (*coord[i])[1] == 'n')    
		{
			float tmpx, tmpy, tmpz;

			//Read the 3 floats, which makes up the normal
			sscanf(coord[i]->c_str(), "vn %f %f %f", &tmpx, &tmpy, &tmpz);
			
			//And put it in the normal vector
			normals.push_back(new Vector3D(tmpx, tmpy, tmpz));
			
			isnormals = true;
		}
		//If it's a face
		else if ((*coord[i])[0] == 'f')   
		{
			int a, b, c, d, e;
			
			//If this is a quad
			if (count(coord[i]->begin(), coord[i]->end(), ' ') == 4)     
			{
				//If it contains a normal vector, but doesn't contain a texture coorinate
				if (coord[i]->find("//") != string::npos)     
				{
					//Read in this form
					sscanf(coord[i]->c_str(), "f %d//%d %d//%d %d//%d %d//%d", &a, &b, &c, &b, &d, &b, &e, &b);      
					
					//We don't care about the texture coorinate in this case
					faces.push_back(new face(b, a, c, d, e, 0, 0, 0, 0, curmat));    
				}
				//If we have texture coorinate and normal vectors
				else if (coord[i]->find("/") != string::npos)        
				{
					//Texture Coorinates
					int t[4];       

					//Read in this form, and put to the end of the vector
					sscanf(coord[i]->c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &a, &t[0], &b, &c, &t[1], &b, &d, &t[2], &b, &e, &t[3], &b);
					faces.push_back(new face(b, a, c, d, e, t[0], t[1], t[2], t[3], curmat));
				}
				//Else we don't have normal vectors or texture coorinates
				else
				{
					sscanf(coord[i]->c_str(), "f %d %d %d %d", &a, &b, &c, &d);
					faces.push_back(new face(-1, a, b, c, d, 0, 0, 0, 0, curmat));
				}
			}
			//If it's a triangle
			else
			{  
				//Do the same, except we use one less vertex/texture coorinate/face number
				if (coord[i]->find("//") != string::npos)
				{
					sscanf(coord[i]->c_str(), "f %d//%d %d//%d %d//%d", &a, &b, &c, &b, &d, &b);
					
					faces.push_back(new face(b, a, c, d, 0, 0, 0, curmat));
				}
				else if (coord[i]->find("/") != string::npos)
				{
					int t[3];
					
					sscanf(coord[i]->c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &a, &t[0], &b, &c, &t[1], &b, &d, &t[2], &b);
					
					faces.push_back(new face(b, a, c, d, t[0], t[1], t[2], curmat));
				}
				else
				{
					sscanf(coord[i]->c_str(), "f %d %d %d", &a, &b, &c);
					
					faces.push_back(new face(-1, a, b, c, 0, 0, 0, curmat));
				}
			}
		}
		//Use material_name
		else if ((*coord[i])[0] == 'u' && (*coord[i])[1] == 's' && (*coord[i])[2] == 'e')     
		{
			char tmp[200];
			
			//Read the name of the material to tmp
			sscanf(coord[i]->c_str(), "usemtl %s", tmp);  

			//Go through all of the materials
			for (int i = 0; i<materials.size(); i++)     
			{
				//And compare the tmp with the name of the material
				if (strcmp(materials[i]->name.c_str(), tmp) == 0)   
				{
					//If it's equal then set the current material to that
					curmat = i;       
					break;
				}
			}
		}
		//Material library, a file, which contain all of the materials
		else if ((*coord[i])[0] == 'm' && (*coord[i])[1] == 't' && (*coord[i])[2] == 'l' && (*coord[i])[3] == 'l')      
		{
			char filen[200];
			
			//Read the fileName
			sscanf(coord[i]->c_str(), "mtllib %s", filen);    
			
			//Open the file
			ifstream mtlin(filen);     
			
			//If not opened, show a error message, clean all memory, then return with -1
			if (!mtlin.is_open())    
			{
				cout << "connot open the material file" << endl;
				clean();
				return -1;
			}
			
			//We use materials
			ismaterial = true;        
			
			//Contain the line of the file
			vector<string> tmp;
			
			char c[200];
			
			while (!mtlin.eof())
			{
				//Read all lines to tmp
				mtlin.getline(c, 200);   
				tmp.push_back(c);
			}
			
			//Name of the material
			char name[200]; 
			
			//fileName of the texture
			char fileName[200];     
			
			//Colors, shininess, etc
			float amb[3], dif[3], spec[3], alpha, ns, ni;        
			
			int illum;
			unsigned int texture;
			
			//Do we already have a material read in to these variables?
			bool ismat = false;       

			//Set fileName to nullbyte character
			strcpy(fileName, "\0");  
			
			//Go through all lines of the mtllib file
			for (int i = 0; i<tmp.size(); i++) 
			{
				//Ignore comments
				if (tmp[i][0] == '#')      
					continue;
				
				//New material
				if (tmp[i][0] == 'n' && tmp[i][1] == 'e' && tmp[i][2] == 'w')  
				{
					//If we have a material
					if (ismat)       
					{
						//If we have a texture
						if (strcmp(fileName, "\0") != 0)    
						{
							//Push back
							materials.push_back(new materialObj(name, alpha, ns, ni, dif, amb, spec, illum, texture)); 
							strcpy(fileName, "\0");
						}
						//Push back, but use -1 to texture
						else
						{
							materials.push_back(new materialObj(name, alpha, ns, ni, dif, amb, spec, illum, -1));                           
						}
					}
					//We start from a fresh material
					ismat = false;    
					
					//Read in the name
					sscanf(tmp[i].c_str(), "newmtl %s", name);        
				}
				//Shininess
				else if (tmp[i][0] == 'N' && tmp[i][1] == 's')      
				{
					sscanf(tmp[i].c_str(), "Ns %f", &ns);
					ismat = true;
				}
				//Ambient
				else if (tmp[i][0] == 'K' && tmp[i][1] == 'a')      
				{
					sscanf(tmp[i].c_str(), "Ka %f %f %f", &amb[0], &amb[1], &amb[2]);
					ismat = true;
				}
				//Diffuse
				else if (tmp[i][0] == 'K' && tmp[i][1] == 'd')      
				{
					sscanf(tmp[i].c_str(), "Kd %f %f %f", &dif[0], &dif[1], &dif[2]);
					ismat = true;
				}
				//Specular
				else if (tmp[i][0] == 'K' && tmp[i][1] == 's')
				{
					sscanf(tmp[i].c_str(), "Ks %f %f %f", &spec[0], &spec[1], &spec[2]);
					ismat = true;
				}
				//Others
				else if (tmp[i][0] == 'N' && tmp[i][1] == 'i')      
				{
					sscanf(tmp[i].c_str(), "Ni %f", &ni);
					ismat = true;
				}
				//Alpha
				else if (tmp[i][0] == 'd' && tmp[i][1] == ' ')      
				{
					sscanf(tmp[i].c_str(), "d %f", &alpha);
					ismat = true;
				}
				//Illum (Not Used)
				else if (tmp[i][0] == 'i' && tmp[i][1] == 'l')      
				{
					sscanf(tmp[i].c_str(), "illum %d", &illum);
					ismat = true;
				}
				//Texture
				else if (tmp[i][0] == 'm' && tmp[i][1] == 'a')      
				{
					sscanf(tmp[i].c_str(), "map_Kd %s", fileName);

					//Read the fileName, and use the loadTexture function to load it, and get the id.
					texture = loadTexture(fileName);  
					ismat = true;
				}
			}
			//There is no newmat after the last newmat, so we have to put the last material 'manually'
			if (ismat)       
			{
				if (strcmp(fileName, "\0") != 0)
				{
					materials.push_back(new materialObj(name, alpha, ns, ni, dif, amb, spec, illum, texture));
				}
				else{
					materials.push_back(new materialObj(name, alpha, ns, ni, dif, amb, spec, illum, -1));
				}
			}
		}
		//Back to the obj file, texture coorinate
		else if ((*coord[i])[0] == 'v' && (*coord[i])[1] == 't')    
		{
			float u, v;

			//Read the uv coordinate
			sscanf(coord[i]->c_str(), "vt %f %f", &u, &v);     
			
			//I push back 1-v instead of normal v, because obj file use the upper left corner as 0,0 coordinate
			texturecoordinate.push_back(new texcoordObj(u, 1 - v));       
			
			//OpenGL usesvthe bottom left corner as 0, 0, so  convert it
			istexture = true;
		}
	}
	
	//If for some reason the material file doesn't contain any material, we don't have a material
	if (materials.size() == 0) 
		ismaterial = false;
	//Else we have a material
	else    
		ismaterial = true;

	//Debug purposes
	//cout << vertex.size() << " " << normals.size() << " " << faces.size() << " " << materials.size() << endl;    
	
	//Draw
	int num;

	//I generate a unique identifier for the list
	num = glGenLists(1);
	glNewList(num, GL_COMPILE);

	//The last material (default -1, which doesn't exist, so we use the first material)
	int last = -1;  

	//Go through all faces
	for (int i = 0; i<faces.size(); i++) 
	{
		//If we have a meterial AND the last material is not the same
		if (last != faces[i]->mat && ismaterial)   
		{
			//Set all of the material property
			float diffuse[] = { materials[faces[i]->mat]->dif[0], materials[faces[i]->mat]->dif[1], materials[faces[i]->mat]->dif[2], 1.0 };
			float ambient[] = { materials[faces[i]->mat]->amb[0], materials[faces[i]->mat]->amb[1], materials[faces[i]->mat]->amb[2], 1.0 };
			float specular[] = { materials[faces[i]->mat]->spec[0], materials[faces[i]->mat]->spec[1], materials[faces[i]->mat]->spec[2], 1.0 };
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
			glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
			glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
			glMaterialf(GL_FRONT, GL_SHININESS, materials[faces[i]->mat]->ns);

			//Set the current to last
			last = faces[i]->mat;     

			//if we don't have texture, disable it, else enable it
			if (materials[faces[i]->mat]->texture == -1)       
				glDisable(GL_TEXTURE_2D);
			else
			{
				glEnable(GL_TEXTURE_2D);

				//And use it
				glBindTexture(GL_TEXTURE_2D, materials[faces[i]->mat]->texture); 
			}
		}
		//If quad
		if (faces[i]->four)      
		{
			//glBegin(GL_QUADS);
			//
			////If there are normals
			//if (isnormals)
			//{
			//	//Use them
			//	glNormal3f(normals[faces[i]->facenum - 1]->x, normals[faces[i]->facenum - 1]->y, normals[faces[i]->facenum - 1]->z);    
			//}

			//////If there are textures
			////if (istexture && materials[faces[i]->mat]->texture != -1)  
			////{
			//	////Set the texture coorinate
			//	//glTexCoord2f(texturecoordinate[faces[i]->texcoord[0] - 1]->u, texturecoordinate[faces[i]->texcoord[0] - 1]->v);      
			////}

			//glVertex3f(vertex[faces[i]->faces[0] - 1]->x, vertex[faces[i]->faces[0] - 1]->y, vertex[faces[i]->faces[0] - 1]->z);

			///*if (istexture && materials[faces[i]->mat]->texture != -1)
			//	glTexCoord2f(texturecoordinate[faces[i]->texcoord[1] - 1]->u, texturecoordinate[faces[i]->texcoord[1] - 1]->v);*/

			//glVertex3f(vertex[faces[i]->faces[1] - 1]->x, vertex[faces[i]->faces[1] - 1]->y, vertex[faces[i]->faces[1] - 1]->z);

			///*if (istexture && materials[faces[i]->mat]->texture != -1)
			//	glTexCoord2f(texturecoordinate[faces[i]->texcoord[2] - 1]->u, texturecoordinate[faces[i]->texcoord[2] - 1]->v);*/

			//glVertex3f(vertex[faces[i]->faces[2] - 1]->x, vertex[faces[i]->faces[2] - 1]->y, vertex[faces[i]->faces[2] - 1]->z);

			///*if (istexture && materials[faces[i]->mat]->texture != -1)
			//	glTexCoord2f(texturecoordinate[faces[i]->texcoord[3] - 1]->u, texturecoordinate[faces[i]->texcoord[3] - 1]->v);*/

			//glVertex3f(vertex[faces[i]->faces[3] - 1]->x, vertex[faces[i]->faces[3] - 1]->y, vertex[faces[i]->faces[3] - 1]->z);
			//glEnd();
		}
		else
		{
			glBegin(GL_TRIANGLES);
			
			//If there are normals
			if (isnormals)   
				glNormal3f(normals[faces[i]->facenum - 1]->x, normals[faces[i]->facenum - 1]->y, normals[faces[i]->facenum - 1]->z);

			//if (istexture && materials[faces[i]->mat]->texture != -1)
				//glTexCoord2f(texturecoordinate[faces[i]->texcoord[0] - 1]->u, texturecoordinate[faces[i]->texcoord[0] - 1]->v);

			glVertex3f(vertex[faces[i]->faces[0] - 1]->x, vertex[faces[i]->faces[0] - 1]->y, vertex[faces[i]->faces[0] - 1]->z);

			//if (istexture && materials[faces[i]->mat]->texture != -1)
				//glTexCoord2f(texturecoordinate[faces[i]->texcoord[1] - 1]->u, texturecoordinate[faces[i]->texcoord[1] - 1]->v);

			glVertex3f(vertex[faces[i]->faces[1] - 1]->x, vertex[faces[i]->faces[1] - 1]->y, vertex[faces[i]->faces[1] - 1]->z);

			//if (istexture && materials[faces[i]->mat]->texture != -1)
				//glTexCoord2f(texturecoordinate[faces[i]->texcoord[2] - 1]->u, texturecoordinate[faces[i]->texcoord[2] - 1]->v);

			glVertex3f(vertex[faces[i]->faces[2] - 1]->x, vertex[faces[i]->faces[2] - 1]->y, vertex[faces[i]->faces[2] - 1]->z);
			glEnd();
		}
	}
	glEndList();
	clean();
	lists.push_back(num);
	return num;
}

void ObjLoader::clean()
{
	//Delete all the dynamically allocated memory
	for (int i = 0; i<coord.size(); i++)
		delete coord[i];

	for (int i = 0; i<faces.size(); i++)
		delete faces[i];

	for (int i = 0; i<normals.size(); i++)
		delete normals[i];

	for (int i = 0; i<vertex.size(); i++)
		delete vertex[i];

	for (int i = 0; i<materials.size(); i++)
		delete materials[i];

	for (int i = 0; i<texturecoordinate.size(); i++)
		delete texturecoordinate[i];

	//And all elements from the vector
	coord.clear();
	faces.clear();
	normals.clear();
	vertex.clear();
	materials.clear();
	texturecoordinate.clear();
}

//Load the fileName textures (only BMP, R5G6B5 format)
unsigned int ObjLoader::loadTexture(const char* fileName)
{
	unsigned int num;
	glGenTextures(1, &num);
	SDL_Surface* img = SDL_LoadBMP(fileName);
	glBindTexture(GL_TEXTURE_2D, num);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->w, img->h, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, img->pixels);
	glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);       
	SDL_FreeSurface(img);
	texture.push_back(num);
	return num;
}