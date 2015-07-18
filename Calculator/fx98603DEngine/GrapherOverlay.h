#ifndef GRAPHEROVERLAY_H
#define GRAPHEROVERLAY_H

#include "Renderer.h"
#include "ButtonUI.h"
#include "Vector.h"
#include "Function.h"
#include "uString.h"

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
	UIModes UIMode;

	ButtonUI TraceBut;
	Vector TraceLoc;

	Function *func;

	void DrawCurser(int x, int y);

	void reset();
public:
	GrapherOverlay();

	bool InputFromGrapherOverlay();
#if _MSC_VER != 1200
	bool Input(SDL_Event * e, Function * functions[]);
#endif

#if _MSC_VER == 1200
	bool Input(unsigned int * key);
#endif

	bool Proccess();

	void Display(Renderer* gRenderer);
};

#endif