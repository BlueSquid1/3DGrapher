#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include "Matrix.h"
#include "Vector.h"

//4x4 matrices used so offen I made a class just for it
//Able to use the stack instead of the heap for memory (massive speed boast)
class Matrix4x4 : public Matrix
{
	float* mainArr[4];
	float mem0[4];
	float mem1[4];
	float mem2[4];
	float mem3[4];

	float mem[4][4];

public:
	Matrix4x4(float initValue = 0.0);

	Matrix4x4 operator*(const Matrix4x4& matA) const;
	Matrix4x4 operator*(const Vector& matA) const;

	Matrix4x4 Inverse();
	~Matrix4x4();
};

#endif