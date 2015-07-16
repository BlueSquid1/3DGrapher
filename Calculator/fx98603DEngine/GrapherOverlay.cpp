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
#if _MSC_VER != 1200
	this->TraceBut.SetTrigger(SDLK_F1);
#endif
#if _MSC_VER == 1200
	this->TraceBut.SetTrigger(KEY_CTRL_F1);
#endif
}

bool GrapherOverlay::InputFromGrapherOverlay()
{
	return UIMode != NONE;
}

#if _MSC_VER != 1200
bool GrapherOverlay::Input(SDL_Event * e)
{
	if (TraceBut.HandleEvent(e))
	{
		UIMode = TRACER;
	}

	return true;
}
#endif

#if _MSC_VER == 1200
bool GrapherOverlay::Input(unsigned int * key)
{
	if(TraceBut.HandleEvent(key))
	{
		UIMode = TRACER;
	}
	return true;
}
#endif



void GrapherOverlay::Display(Renderer* gRenderer)
{
	//Render the buttons
	TraceBut.Render(gRenderer);
}