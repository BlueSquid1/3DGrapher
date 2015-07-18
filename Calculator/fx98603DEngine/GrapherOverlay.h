#ifndef GRAPHEROVERLAY_H
#define GRAPHEROVERLAY_H

#include "Renderer.h"
#include "ButtonUI.h"
#include "Vector.h"
#include "Function.h"
#include "uString.h"
#include "Evaluate.h"
#include "View.h"
#include "Point.h"

#if _MSC_VER != 1200
	#include <SDL.h>
#endif
#if _MSC_VER == 1200
	#include <fxlib.h>
#endif

#ifndef NULL
	#define NULL 0
#endif

enum UIModes
{
	NONE,
	TRACER
};

class GrapherOverlay
{
	Renderer * gRenderer;
	View * cam;

	UIModes UIMode;

	ButtonUI TraceBut;
	Vector TraceLoc;
	Point PixelsLoc;

	Function *func;

	void DrawCoor();
	void DrawCurser(int x, int y);

	void reset();
public:
	GrapherOverlay(Renderer* gRenderer, View * mCam);

	bool InputFromGrapherOverlay();
#if _MSC_VER != 1200
	bool Input(SDL_Event * e, Function * functions[]);
#endif

#if _MSC_VER == 1200
	bool Input(unsigned int * key, Function * functions[]);
#endif

	bool Proccess();

	void Display();
};

#endif