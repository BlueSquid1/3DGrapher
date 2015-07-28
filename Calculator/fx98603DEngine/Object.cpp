#include "Object.h"

Object::Object()
{
	//set transMat to the identity matrix
	TransMat(0, 0) = 1.0;
	TransMat(1, 1) = 1.0;
	TransMat(2, 2) = 1.0;
	TransMat(3, 3) = 1.0;
	
	//will update the inverse matrix
	needUpdate = true;
}

bool Object::ScaleGlobal(const float& x, const float& y, const float& z)
{
	Matrix4x4 scaleMat;

	scaleMat(3, 3) = 1.0;
	
	scaleMat(0,0) = x;
	
	scaleMat(1,1) = y;
	
	scaleMat(2,2) = z;
	
	//update TransMat
	TransMat = scaleMat * TransMat;
	
	needUpdate = true;

	return true;
}

bool Object::RotateGlobal(const float& angdX, const float& angdY, const float& angdZ)
{
	//convert from degrees to radians
	
	float angX = (PI / 180.0) * angdX;
	
	float angY = (PI / 180.0) * angdY;
	
	float angZ = (PI / 180.0) * angdZ;
	
	
	//rotations around X axis
	Matrix4x4 rotX;
	rotX(0,0) = 1;
	rotX(1,1) = cos(angX);
	rotX(1,2) = -sin(angX);
	rotX(2,1) = sin(angX);
	rotX(2,2) = cos(angX);
	rotX(3,3) = 1;
	
	//rotations around Y axis
	Matrix4x4 rotY;
	rotY(0,0) = cos(angY);
	rotY(0,2) = sin(angY);
	rotY(1,1) = 1;
	rotY(2,0) = -sin(angY);
	rotY(2,2) = cos(angY);
	rotY(3,3) = 1;
	
	//rotations around Z axis
	Matrix4x4 rotZ;
	rotZ(0,0) = cos(angZ);
	rotZ(0,1) = -sin(angZ);
	rotZ(1,0) = sin(angZ);
	rotZ(1,1) = cos(angZ);
	rotZ(2,2) = 1;
	rotZ(3,3) = 1;
	
	TransMat = rotZ * rotY * rotX * TransMat;
	
	needUpdate = true;
	
	return true;
}


bool Object::TranslationGlobal(const float& x, const float& y, const float& z)
{
	Matrix4x4 TranslationalMat;
	TranslationalMat(0,0) = 1;
	TranslationalMat(1,1) = 1;
	TranslationalMat(2,2) = 1;
	TranslationalMat(3,3) = 1;
	
	TranslationalMat(0,3) = x;
	TranslationalMat(1,3) = y;
	TranslationalMat(2,3) = z;
	
	TransMat = TranslationalMat * TransMat;
	
	needUpdate = true;
	
	return true;
}

bool Object::TranslationLocal(const float& x, const float& y, const float& z)
{
	Vector TranslationalVec(x, y, z);

	Matrix4x4 TranslationResults = TransMat * TranslationalVec;

	this->TransMat(0, 3) = TranslationResults(0, 0);
	this->TransMat(1, 3) = TranslationResults(1, 0);
	this->TransMat(2, 3) = TranslationResults(2, 0);
	this->TransMat(3, 3) = TranslationResults(3, 0);

	needUpdate = true;

	return true;
}

bool Object::ResetMatrix()
{
	TransMat(0, 0) = 1.0;
	TransMat(1, 1) = 1.0;
	TransMat(2, 2) = 1.0;
	TransMat(3, 3) = 1.0;

	needUpdate = true;
	return true;
}

Matrix4x4& Object::GetMat()
{
	return TransMat;
}

Matrix4x4& Object::GetInverse()
{
	//check to see if TransMat has changed
	if(needUpdate == false)
	{
		return InverseMat;
	}
	
	//otherwise calculate the inverseMat
	
	this->InverseMat = TransMat.Inverse();
	
	needUpdate = false;
	
	return this->InverseMat;
}