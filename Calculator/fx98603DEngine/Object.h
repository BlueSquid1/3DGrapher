#ifndef OBJECT_H
#define OBJECT_H

extern "C"
{
	#include <math.h>
}

#include "Matrix.h"
#include "Matrix4x4.h"
#include "Vector.h"

#define PI 3.14159265

class Object
{
	Matrix4x4 TransMat;
	//needUpdate
	bool needUpdate;
	Matrix4x4 InverseMat;
public:

	//constructor
	Object();
	
	bool ScaleGlobal(const float& x, const float& y, const float& z);
	
	//in degrees
	virtual bool RotateGlobal(const float& angdX, const float& angdY, const float& angdZ);
	
	bool TranslationGlobal(const float& x, const float& y, const float& z);
	
	bool TranslationLocal(const float& x, const float& y, const float& z);

	//reset everything back to the default
	bool ResetMatrix();

	Matrix4x4& GetMat();

	Matrix4x4& GetInverse();
};

#endif //OBJECT_H