#include "GrapherOverlay.h"

void DrawCurser(int x, int y)
{
	
}

void GrapherOverlay::reset()
{
	if (!this->func)
	{
		uString::ErrorPrint("func for override interface has not been set");
	}
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
	
	TraceLoc(0) = 0.0;
	TraceLoc(1) = 0.0;
	TraceLoc(2) = 0.0;

	this->func = NULL;
}

bool GrapherOverlay::InputFromGrapherOverlay()
{
	return UIMode != NONE;
}

#if _MSC_VER != 1200
bool GrapherOverlay::Input(SDL_Event * e, Function * functions[])
{
	//if not activated
	if (UIMode == NONE)
	{
		//see if trace has been triggered
		if (TraceBut.HandleEvent(e))
		{
			UIMode = TRACER;
			this->func = functions[0];
			reset();
		}
	}


	return true;
}
#endif

#if _MSC_VER == 1200
bool GrapherOverlay::Input(unsigned int * key)
{
	//if not activated
	if (UIMode == NONE)
	{
		if(TraceBut.HandleEvent(key))
		{
			UIMode = TRACER;
			this->func = functions[0];
			reset();
		}
	}
	return true;
}
#endif

bool GrapherOverlay::Proccess()
{
	return true;
}


void GrapherOverlay::Display(Renderer* gRenderer)
{
	//Render the buttons
	TraceBut.Render(gRenderer);
	
	if (UIMode == TRACER)
	{
		gRenderer->DrawBox(0, 0,10,10,0);
		//draw curser
	}
}