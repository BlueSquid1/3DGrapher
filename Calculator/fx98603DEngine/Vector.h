#ifndef VECTOR_H
#define VECTOR_H

#include "Matrix.h"

//special type of matrix that is (4 x 1)
class Vector : public Matrix
{
public:
	
	//constructor
	Vector();

	//constructor for setting values
	Vector(const float& x, const float& y, const float& z);
	
	//
	void SetValues(const float& x, const float& y, const float& z);

	void operator=(const Matrix& matA);

	~Vector();
	
};

#endif //VECTOR_H