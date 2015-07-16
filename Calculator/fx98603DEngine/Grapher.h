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
#include "VWindow.h"
#include "GrapherOverlay.h"


#if _MSC_VER != 1200
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

	GrapherOverlay UIOverlay;

	Function* func[6];

	VWindow* ViewWindow;

public:

	//constructor
	Grapher(Renderer* origRenderer, VWindow * origViewWindow);
	
	bool LoadFunctions(Function equation[6]);

	//resets variables back to default
	bool Reset();

	//returns false if the user wants to quit the program
	//otherwise returns true
	bool Input();
	bool Proccess();
	void Display();
	
	//deconstructor
	~Grapher();
};

#endif GRAPHER_H