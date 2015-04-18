#include "Mesh.h"

#ifndef NULL
	#define NULL 0
#endif

#if _MSC_VER == 1800
	#include <iostream>
#endif

Mesh::Mesh() : Object()
{
	this->vertices = NULL;
	this->indicesArray = NULL;
	this->pixels = NULL;

	indicesCount = 0;
}

bool Mesh::SetSpace(const int& vertexSize, const int& indicesSize)
{
	//set space for all dynamic memory in the array
	this->VertexResize(vertexSize);
	this->PixelsResize();
	this->IndicesArrayResize(indicesSize);
	return true;
}

bool Mesh::VertexResize(const int& n)
{
	//first clear any space that was dedicated to Vertices
	if (vertices != NULL)
	{
		delete[] this->vertices;
		this->vertices = NULL;
	}

	vertices = new Vector[n];

	if (!vertices)
	{
		//ran out of space
		return false;
	}

	//write down the number of vertexs
	this->vertexCount = n;

	return true;
}

bool Mesh::PixelsResize()
{
	//first clear any space that was dedicated to Vertices
	if (pixels != NULL)
	{
		delete[] this->pixels;
		this->pixels = NULL;
	}

	pixels = new Vector[this->vertexCount];

	if (!pixels)
	{
		//ran out of space
		return false;
	}

	return true;
}


bool Mesh::IndicesArrayResize(const int& n)
{
	//first clear any space that was dedicated to Vertices
	if (indicesArray != NULL)
	{
		delete[] this->indicesArray;
		this->indicesArray = NULL;
	}

	indicesArray = new int[n];

	if (!indicesArray)
	{
		//ran out of space
		return false;
	}

	//write down the number of indices
	this->indicesCount = n;

	return true;
}

int Mesh::GetIndicesCount()
{
	return this->indicesCount;
}

int Mesh::GetFaceCount()
{
	return indicesCount / 3;
}

int Mesh::GetPixelstCount()
{
	return vertexCount;
}

int Mesh::GetVertexCount()
{
	return vertexCount;
}


Vector& Mesh::GetVertex(const int& i)
{
#if _MSC_VER == 1800
	//check the boundaries
	if (i < 0 || i >= this->GetVertexCount())
	{
		std::cout << "accessing a vector out of boundaries\n";
	}
#endif
	return this->vertices[i];
}

Vector& Mesh::GetPixel(const int& i)
{
#if _MSC_VER == 1800
	//check the boundaries
	if (i < 0 || i >= this->GetPixelstCount())
	{
		std::cout << "accessing a vector out of boundaries\n";
	}
#endif
	return this->pixels[i];
}


int& Mesh::GetIndice(const int& i)
{
#if _MSC_VER == 1800
	//check the boundaries
	if (i < 0 || i >= this->GetIndicesCount())
	{
		std::cout << "accessing a vector out of boundaries\n";
	}
#endif
	return this->indicesArray[i];
}



Mesh::~Mesh()
{
	delete[] this->vertices;

	this->vertices = NULL;

	delete[] this->pixels;
	this->pixels = NULL;

	delete[] this->indicesArray;
	this->indicesArray = NULL;
}

