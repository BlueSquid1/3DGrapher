#include "GrapherOverlay.h"

void GrapherOverlay::DrawCoor()
{
	//because I used blenders coordant system I need to switch the x and the y axis
	char s[20];
	sprintf((char *)s, "x=%.1f", this->TraceLoc(1));
	gRenderer->PrintTextMini(30 * 0, 0, s, 0);

	sprintf((char *)s, "y=%.1f", this->TraceLoc(0));
	gRenderer->PrintTextMini(40 * 1, 0, s, 0);

	sprintf((char *)s, "z=%.1f", this->TraceLoc(2));
	gRenderer->PrintTextMini(40 * 2, 0, s, 0);
}

void GrapherOverlay::DrawCurser(int x, int y)
{
	int width = 3;
	int thick = 1;
	//top
	this->gRenderer->DrawLine(x - thick, y - thick, x - thick, y - width);
	this->gRenderer->DrawLine(x - thick, y - width, x + thick, y - width);
	this->gRenderer->DrawLine(x + thick, y - width, x + thick, y - thick);

	//right
	this->gRenderer->DrawLine(x + thick, y - thick, x + width, y - thick);
	this->gRenderer->DrawLine(x + width, y - thick, x + width, y + thick);
	this->gRenderer->DrawLine(x + width, y + thick, x + thick, y + thick);

	//bottom
	this->gRenderer->DrawLine(x - thick, y + thick, x - thick, y + width);
	this->gRenderer->DrawLine(x - thick, y + width, x + thick, y + width);
	this->gRenderer->DrawLine(x + thick, y + width, x + thick, y + thick);

	//left
	this->gRenderer->DrawLine(x - thick, y - thick, x - width, y - thick);
	this->gRenderer->DrawLine(x - width, y - thick, x - width, y + thick);
	this->gRenderer->DrawLine(x - width, y + thick, x - thick, y + thick);

	//fill in white spaces
	this->gRenderer->DrawLine(x, y - 2, x, y + 2, false);
	this->gRenderer->DrawLine(x - 2, y, x + 2, y, false);

	//dot in centre
	this->gRenderer->DrawLine(x, y, x, y);

}

void GrapherOverlay::DrawAxes()
{

}

void GrapherOverlay::reset()
{
	if (!this->func)
	{
		uString::ErrorPrint("func for override interface has not been set");
		return;
	}

	TraceLoc(0) = (this->func->GetUpperBoundary()(0) + this->func->GetLowerBoundary()(0)) /2.0;
	TraceLoc(1) = (this->func->GetUpperBoundary()(1) + this->func->GetLowerBoundary()(1)) /2.0;
}

GrapherOverlay::GrapherOverlay(Renderer* mGRenderer, View * mCam, VWindow * origViewWindow)
{
	this->gRenderer = mGRenderer;
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

	this->AutoZoom.SetPos(21 * 1, 7 * 8);
	this->AutoZoom.SetText("Auto");

	this->func = NULL;
	cam = mCam;
	ViewWindow = origViewWindow;
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
	else if (UIMode == TRACER)
	{
		if (gRenderer->e.type == SDL_KEYDOWN)
		{
			float xRange = func->GetUpperBoundary()(0) - func->GetLowerBoundary()(0);
			float yRange = func->GetUpperBoundary()(1) - func->GetLowerBoundary()(1);

			switch (gRenderer->e.key.keysym.sym)
			{
			case SDLK_RIGHT:
				TraceLoc(0) += xRange/50.0;
				break;

			case SDLK_LEFT:
				TraceLoc(0) -= xRange / 50.0;
				break;

			case SDLK_UP:
				TraceLoc(1) += yRange / 50.0;
				break;
			case SDLK_DOWN:
				TraceLoc(1) -= yRange / 50.0;
				break;
			case SDLK_ESCAPE:
				UIMode = NONE;
				break;
			case SDLK_F1:
				UIMode = NONE;
				break;
			}
		}
	}


	return true;
}
#endif

#if _MSC_VER == 1200
bool GrapherOverlay::Input(unsigned int * key, Function * functions[])
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
	else if (UIMode == TRACER)
	{
		float xRange = func->GetUpperBoundary()(0) - func->GetLowerBoundary()(0);
		float yRange = func->GetUpperBoundary()(1) - func->GetLowerBoundary()(1);

		switch (*key)
		{
		case KEY_CTRL_RIGHT:
			TraceLoc(0) += xRange / 50.0;
			break;

		case KEY_CTRL_LEFT:
			TraceLoc(0) -= xRange / 50.0;
			break;

		case KEY_CTRL_UP:
			TraceLoc(1) += yRange / 50.0;
			break;
		case KEY_CTRL_DOWN:
			TraceLoc(1) -= yRange / 50.0;
			break;
		case KEY_CTRL_EXIT:
			UIMode = NONE;
			break;
		case KEY_CTRL_F1:
			UIMode = NONE;
			break;
		}
	}
	return true;
}
#endif

bool GrapherOverlay::Proccess()
{
	if (UIMode == TRACER)
	{
		//check boundaries
		if (TraceLoc(0) < func->GetLowerBoundary()(0))
		{
			TraceLoc(0) = func->GetLowerBoundary()(0);
		}
		else if (TraceLoc(0) > func->GetUpperBoundary()(0))
		{
			TraceLoc(0) = func->GetUpperBoundary()(0);
		}

		if (TraceLoc(1) < func->GetLowerBoundary()(0))
		{
			TraceLoc(1) = func->GetLowerBoundary()(1);
		}
		else if (TraceLoc(1) > func->GetUpperBoundary()(1))
		{
			TraceLoc(1) = func->GetUpperBoundary()(1);
		}

		//work out the z value from function
		int eCode = 0;
		float result = 0.0;
		result = Evaluate::Eval(func->GetEquation(), TraceLoc(0), TraceLoc(1), &eCode);

		//enter z value
		TraceLoc(2) = result;

		//project curser so can be displayed on screen
		PixelsLoc = cam->Project3Dto2D(TraceLoc);
	}
	return true;
}


void GrapherOverlay::Display()
{
	//Render the buttons
	TraceBut.Render(gRenderer);
	AutoZoom.Render(gRenderer);

	if (ViewWindow->GetSettings().DisplayAxes == true)
	{
		DrawAxes();
	}

	if (UIMode == TRACER)
	{
		//draw curser
		this->DrawCurser(PixelsLoc.x, PixelsLoc.y);

		//draw coordiants
		DrawCoor();
	}
}