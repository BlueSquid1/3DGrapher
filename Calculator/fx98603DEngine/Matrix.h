#ifndef MATRIX_H
#define MATRIX_H

#ifndef NULL
   #define NULL 0
#endif

extern "C"
{
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h> // abs()
	#include <math.h> // pow()
}

#if _MSC_VER != 1200
	#include <iostream>
#endif

#include "uString.h" //error prints

class Matrix
{
	friend class Vector;
	friend class Matrix4x4;
	
	//matrix dimentions
	//------------------
	int c; //columns in x dirrection
	int r; //rows in y dirrection
	//==================
	
	//store the values in the matrix
	float **m; //effected by Trans(), Det(), Inverse()

	//private methods
	//---------------
	float& val(const int& y, const int& x); //able to read and write
	float valC(const int& y, const int& x) const; //read only. to stop the compilar from being a bitch
	void ClearArray(); //wipe clean the array
	bool SetSpace(const int& mRows, const int& mCols);
	static float Determ(float ** a, const int& n);	//find the determ of the submatrix
	Matrix GenSubMatrix(const int& ay, const int& ax) const; //Make a sub matrix not including colum ay and row ax
	//---------------
	
public:
	
	
	//finds the identity matrix n by n
	// FUNCTION: Identity
	//
	// PURPOSE: generate an Identity matrix
	//
	// COMMENTS:
	// Identity matrix is size n by n.
	// static function. therefore does not need an
	// existing matrix to use.
	// Does not effect any other matrixes
	static Matrix Identity(const int& n);
	

	// FUNCTION: Constructor
	//
	// PURPOSE: Initalize the member variables
	//
	// COMMENTS:
	// mRows is the number of rows the matrix should be.
	// mCols is the number of columns the matrix should be.
	// initValue is the value each element of the matrix should start at.
	Matrix(int mRows = 1, int mCols = 1, float initValue = 0.0);
	
	
	// FUNCTION: Copy Constructor
	// 
	// PURPOSE: performs a deep copy of an existing matrix
	//
	// COMMENTS:
	// matA is the matrix to copy the values from.
	// dimensions are taken from matA
	Matrix (const Matrix & matA);
	
	//
	Matrix& Set(int mRows = 1, int mCols = 1, float initValue = 0.0);

	
	// FUNCTION: Assignment Operator
	//
	// PURPOSE: performs a deep copy of an existing matrix
	//
	// COMMENTS:
	// matA is the matrix to copy the values from.
	// Does a dimension check before copying
	// return void so nothing useful can be on the left side of "="
	void operator=(const Matrix& matA);
	
	
	// FUNCTION: Round Bracket Operation
	//
	// PURPOSE: returns the element value at position (y,x)
	//
	// COMMENTS:
	// y is the number of columns down from the top left corner
	// x is the number of rows down from the top left corner
	// returns reference. therefore CAN write and read value
	float& operator()(const int& y, const int& x = 0);
	
	
	// FUNCTION: Plus Operation
	// 
	// PURPOSE: matrix addition
	//
	// COMMENTS:
	// returns the sum of matrix *this and matA.
	// where matrix *this is the one on the left of the '+' symbol
	// returns as copy. Does not alter *this
	Matrix operator+(const Matrix& matA) const;
	
	
	// FUNCTION: Minus Operation
	//
	// PURPOSE: matrix subtraction
	//
	// COMMENTS:
	// returns the difference between matrix *this and matA.
	// where matrix *this is the one on the left of the '-' symbol
	// returns as copy. Does not alter *this
	Matrix operator-(const Matrix& matA) const;
	
	
	// FUNCTION: Unary Minus
	//
	// PURPOSE: Unary Minus to a matrix
	//
	// COMMENTS:
	// returns the negative matrix
	// '-' symbol must be on the left hand side of *this
	// return as copy. Does not alter *this
	Matrix operator-() const;
	
	
	// FUNCTION: Multiplication Operation
	//
	// PURPOSE: matrix multiplication
	//
	// COMMENTS:
	// returns the multiplication result between this* and matA.
	// rows of *this must equal columns of matA
	// return as copy. Does not alter *this
	Matrix operator*(const Matrix& matA) const;
	
	
	// FUNCTION: Scaler Multiplication Operation (from the right)
	//
	// PURPOSE: scaler matrix multiplication
	//
	// COMMENTS:
	// returns the scaler multiplication result between this8 and valA
	// when possible use operator-() instead. it has better performance.
	// method called when valA is on the right of *this
	// return as copy. Does not alter *this
	Matrix operator*(const float& valA) const;
	
	// FUNCTION: Scaler Multiplication Operation (from the left)
	//
	// PURPOSE: scaler matrix multiplication
	//
	// COMMENTS:
	// returns the scaler multiplication result between this8 and valA
	// when possible use operator-() instead. it has better performance.
	// method called when valA is on the left of *this
	// return as copy. Does not alter *this
	friend Matrix operator*(const float& valA, const Matrix& matA);
	
	Matrix operator/(const float& valA) const;
	
	// FUNCTION: Multiplication and Assignment Operation
	//
	// PURPOSE: Matrix multiplication and assignment
	//
	// COMMENTS:
	// first calculates *this * matA
	// then assigns the resulting matrix to *this
	// there is room for speeding up this method however
	// the current algorithm is much easier to read.
	// I might come back later to optimize this method.
	// method call overwrites *this. Use with care!
	Matrix& operator*=(const Matrix& matA);
	
	
	// FUNCTION: Power Operator
	//
	// PURPOSE: Matrix powers
	//
	// COMMENTS:
	// raises matrix *this to the power of valA.
	// matrix *this must be a square matrix.
	// if valA is 0 returns the identity matrix with dimensions
	// the size of *this.
	// if valA is negative then finds the inverse first
	// return as copy. Does not alter *this
	Matrix operator^(const int& valA) const;
	
	// FUNCTION: Trans
	//
	// PURPOSE: find the transpose of the matrix
	//
	// COMMENTS:
	// Copy the values in *this.
	// flip and return the new matrix.
	// return as copy. Does not alter *this
	Matrix Trans() const;
	
	
	// FUNCTION: Det
	//
	// PURPOSE: find the determinant of a matrix
	//
	// COMMENTS:
	// use divide and conquer with recursive function.
	// might be possible to improve performance
	// Does not effect original matrix
	float Det() const;
	
	// FUNCTION: Adj
	//
	// PURPOSE: find the adjoint matrix from *this
	//
	// COMMENTS:
	// first generates a submatrix from *this.
	// then find determinative of submatrix with method Det()
	// stores all the submatrix determinative and returns
	// return as copy. Does not alter *this
	Matrix Adj() const;
	
	
	// FUNCTION: Inverse
	//
	// COMMENTS:
	// Works out determinative tests to see if it is zero
	// then works out adj.
	// returns inverse matrix using formula: Inverse = (1/det) * adj(A)
	// if fails returns the initial *this
	// method call overwrites *this. Use with care!
	Matrix Inverse();
	
	bool operator==(const Matrix& matA) const;
	
	#if _MSC_VER != 1200
	//print with a message
	void Print(const char msg[] = " ") const;
	#endif //_MSC_VER
	
	
	//deconstructor
	~Matrix();
	
	//mutaic functions
	//-----------------
	int Rows() const;
	int Cols() const;
	//=================
	
};

#endif //MATRIX_H