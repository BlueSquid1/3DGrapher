#include "Renderer.h"


Renderer::Renderer(const int& width, const int& height)
	:SCREEN_WIDTH(width), SCREEN_HEIGHT(height)
{
#if _MSC_VER == 1800
	gRenderer = NULL;
	gWindow = NULL;

	//set default colour
	SDL_SetRenderDrawColor(this->gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
#endif
}

#if _MSC_VER == 1800
bool Renderer::SetColour(const Uint8& r, const Uint8& g, const Uint8& b, const Uint8& a)
{	
	SDL_SetRenderDrawColor(gRenderer, r, g, b, a);
	return true;
}
#endif

void Renderer::DrawLine(const int& x1, const int& y1, const int& x2, const int& y2) const
{
#if _MSC_VER == 1200
	Bdisp_DrawLineVRAM(x1, y1, x2, y2);
#endif

#if _MSC_VER == 1800
	SDL_RenderDrawLine(this->gRenderer, x1, y1, x2, y2);
#endif
	return;
}


void Renderer::PrintTextMini(const int& x, const int& y, const unsigned char* s, const int& drawType) const
{
#if _MSC_VER == 1200
	PrintMini(x,y,s,drawType);
#endif
}

void Renderer::PrintTextXY(const int& x, const int& y, const unsigned char* s, const int& drawType) const
{
#if _MSC_VER == 1200
	PrintXY(x,y,s,drawType);
#endif
}

void Renderer::DrawBox(const int& x1, const int& y1, const int& x2, const int& y2, bool inverted) const
{
#if _MSC_VER == 1200
	if (inverted == false)
	{
		for(int y = y1; y < y2; y++)
		{
			Bdisp_DrawLineVRAM(x1, y, x2, y);
		}
	}
	else
	{
		for(int y = y1; y < y2; y++)
		{
			Bdisp_ClearLineVRAM(x1, y, x2, y);
		}
	}
#endif
}

void Renderer::ClearScreen() const
{
#if _MSC_VER == 1800
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
#endif
#if _MSC_VER == 1200
	Bdisp_AllClr_VRAM();
#endif
}

void Renderer::ClearScreen(Point topLeft, Point botRight) const
{
#if _MSC_VER == 1800
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
#endif
#if _MSC_VER == 1200
	DISPBOX area;
	area.left = topLeft.x;
	area.top = topLeft.y;
	area.right = botRight.x;
	area.bottom = botRight.y;
	Bdisp_AreaClr_VRAM(&area);
#endif
}

void Renderer::UpdateScreen() const
{
#if _MSC_VER == 1800
	SDL_RenderPresent(gRenderer);
#endif
#if _MSC_VER == 1200
	Bdisp_PutDisp_DD();
#endif
}

Renderer::~Renderer()
{
#if _MSC_VER == 1800
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
#endif
}