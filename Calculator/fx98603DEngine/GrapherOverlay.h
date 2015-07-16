#ifndef GRAPHEROVERLAY_H
#define GRAPHEROVERLAY_H

#include "Renderer.h"
#include "ButtonUI.h"

#if _MSC_VER != 1200
	#include <SDL.h>
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

	bool Tracer();
public:
	GrapherOverlay();

	bool InputFromGrapherOverlay();
#if _MSC_VER != 1200
	bool Input(SDL_Event * e);
#endif

#if _MSC_VER == 1200
	bool Input(unsigned int * key);
#endif

	bool Proccess();

	void Display(Renderer* gRenderer);
};

#endif