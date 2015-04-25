#ifndef GRAPHER_H
#define GRAPHER_H

/*
	calculator visual studio version = 1200
	VS12 - 2013 community version = 1800
*/

#include "View.h"
#include "Function.h"
#include "gameStatus.h"
#include "Vector.h"
#include "Point.h"
#include "Triangle.h"
#include "Mesh.h"


#if _MSC_VER == 1800
	#include <iostream>
	#include <SDL.h>
	#include <document.h>
	#include <fstream>
	#include <sstream>
#endif

#if _MSC_VER == 1200
extern "C"
{
	#include <fxlib.h>
	#include <math.h>
}
#endif

class Grapher : public GameStatus
{
	View cam;

	Function* func;

#if _MSC_VER == 1800
	SDL_Event e;
#endif

public:

	//constructor
	Grapher(Renderer* origRenderer);

	//bool LoadEquation(unsigned char* eq, const Vector& min, const Vector& max, const int& yres, const int& xres);
	
	bool LoadFunction(Function* equation);

	//returns false if the user wants to quit the program
	//otherwise returns true
	bool Input();
	bool Proccess();
	void Display();
	
	//deconstructor
	~Grapher();
};

#endif GRAPHER_H