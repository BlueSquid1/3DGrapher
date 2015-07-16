#include "GrapherOverlay.h"

bool GrapherOverlay::Tracer()
{
	return true;
}


GrapherOverlay::GrapherOverlay()
{
	UIMode = NONE;

	this->TraceBut.SetPos(21 * 0, 7 * 8);
	this->TraceBut.SetText("Trce");
}

bool GrapherOverlay::InputFromGrapherOverlay()
{
	return UIMode != NONE;
}

#if _MSC_VER != 1200
bool GrapherOverlay::Input(SDL_Event * e)
{
	switch (e->key.keysym.sym)
	{
	case SDLK_F1:
		//Tracer mode
		UIMode = TRACER;
	}

	return true;
}
#endif

#if _MSC_VER == 1200
bool GrapherOverlay::Input(unsigned int * key)
{
	switch(*key)
	{
	case KEY_CTRL_F1:
		UIMode = TRACER;
	}
}
#endif



void GrapherOverlay::Display(Renderer* gRenderer)
{
	//Render the buttons
	TraceBut.Render(gRenderer);
}