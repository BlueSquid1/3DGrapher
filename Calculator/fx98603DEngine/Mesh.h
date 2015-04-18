#ifndef MESH_H
#define MESH_H



#include "Object.h"
#include "Vector.h"

class Mesh : public Object
{

	Vector * vertices;

	//same size as vertices but store the translated vectors
	Vector * pixels;

	int * indicesArray;

	//the number of vertexs in the mesh
	int vertexCount;

	//the number of indices in the mesh
	int indicesCount;


public:

	//constructor
	Mesh();

	bool SetSpace(const int& vertexSize, const int& indicesSize);

	bool VertexResize(const int& n);

	bool PixelsResize();

	bool IndicesArrayResize(const int& n);

	//mutatic functions
	//----------
	int GetIndicesCount();
	int GetFaceCount();
	int GetPixelstCount();
	int GetVertexCount();

	//can write and read from vertices
	Vector& GetVertex(const int& i);
	//can write and read from vertices
	Vector& GetPixel(const int& i);
	//can write and read to indicesArray
	int& GetIndice(const int& i);
	//----------

	//deconstructor
	~Mesh();

};

#endif