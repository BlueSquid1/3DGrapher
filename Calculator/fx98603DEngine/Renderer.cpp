#include "Renderer.h"

Renderer::Renderer(const int& width, const int& height)
	:SCREEN_WIDTH(width), SCREEN_HEIGHT(height)
{
#if _MSC_VER == 1200
	//assuming calculator is using the default font
	fontWidth = 6;
#endif
#if _MSC_VER != 1200
	gRenderer = NULL;
	gWindow = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "failed to open SDL video. SDL error: " << SDL_GetError() << std::endl;
		return;
	}

	this->gWindow = SDL_CreateWindow("3D Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->SCREEN_WIDTH, this->SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!this->gWindow)
	{
		std::cout << "can't create a window. SDL error: " << SDL_GetError() << std::endl;
		return;
	}

	this->gRenderer = SDL_CreateRenderer(this->gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!this->gRenderer)
	{
		std::cout << "can't create a renderer. SDL error: " << SDL_GetError() << std::endl;
		return;
	}

	//set default colour
	SDL_SetRenderDrawColor(this->gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	//initialize ttf loading
	if (TTF_Init() == -1)
	{
		std::cout << "SDL_TTF could not initialize. TTF error: " << TTF_GetError() << std::endl;
		return;
	}

	//set font
	gFont = TTF_OpenFont("res/VeraMono.ttf", 53);

	if (!gFont)
	{
		std::cout << "can't find: impact.ttf TTF error: " << TTF_GetError() << std::endl;
		return;
	}

	//workout the width of the font
	TTF_SizeText(gFont, " ", &fontWidth, &fontHeight);
	fontWidth = fontWidth * (127.0 / SCREEN_WIDTH);
	fontHeight = fontHeight * (63.0 / SCREEN_WIDTH);
#endif
}

#if _MSC_VER != 1200
bool Renderer::SetColour(const Uint8& r, const Uint8& g, const Uint8& b, const Uint8& a)
{	
	SDL_SetRenderDrawColor(gRenderer, r, g, b, a);
	return true;
}
#endif

void Renderer::DrawLine(int x1, int y1, int x2, int y2, bool inBlack) const
{

	if ((y1 < 0 && y2 < 0) || (y1 > SCREEN_HEIGHT&&y2 > SCREEN_HEIGHT) || (x1 < 0 && x2 < 0) || (x2 > SCREEN_WIDTH&&x1 > SCREEN_WIDTH))
	{
		return;
	}
	if (x1 >= SCREEN_WIDTH)
	{
		if (x1 - x2 == 0)
		{
			return;
		}
		else
		{
			y1 = y2 + (SCREEN_WIDTH - x2) * (y1 - y2) / (x1 - x2);
		}
		x1 = SCREEN_WIDTH;
	}
	if (x1 < 0)
	{
		y1 = y2 - (x2 - 0) * (y1 - y2) / (x1 - x2);
		x1 = 0;
	}
	if (y1 >= SCREEN_HEIGHT)
	{
		if (y1 - y2 == 0)
		{
			return;
		}
		else
		{
			x1 = x2 + (SCREEN_HEIGHT - y2) * (x1 - x2) / (y1 - y2);
			y1 = SCREEN_HEIGHT;
		}
	}
	if (y1 < 0)
	{
		if (y1 - y2 == 0)
		{
			return;
		}
		else
		{
			x1 = x2 - (y2 - 0) * (x1 - x2) / (y1 - y2);
			y1 = 0;
		}
	}

	if (x2 >= SCREEN_WIDTH)
	{
		if (x1 - x2 == 0)
		{
			return;
		}
		else
		{
			y2 = y1 + (SCREEN_WIDTH - x1) * (y1 - y2) / (x1 - x2);
			x2 = SCREEN_WIDTH;
		}
	}

	if (x2 < 0)
	{
		if (x1 - x2 == 0)
		{
			return;
		}
		else
		{
			y2 = y1 - (x1 - 0) * (y1 - y2) / (x1 - x2);
			x2 = 0;
		}
	}
	if (y2 >= SCREEN_HEIGHT)
	{
		if (y1 - y2 == 0)
		{
			return;
		}
		else
		{
			x2 = x1 + (SCREEN_HEIGHT - y1) * (x1 - x2) / (y1 - y2);
			y2 = SCREEN_HEIGHT;
		}
	}
	if (y2 < 0)
	{
		if (y1 - y2 == 0)
		{
			return;
		}
		else
		{
			x2 = x1 - (y1 - 0) * (x1 - x2) / (y1 - y2);
			y2 = 0;
		}
	}



#if _MSC_VER == 1200
	if(inBlack)
	{
		Bdisp_DrawLineVRAM(x1, y1, x2, y2); //black line
	}
	else
	{
		Bdisp_ClearLineVRAM(x1, y1, x2, y2); //white line
	}
#endif

#if _MSC_VER != 1200
	if (inBlack)
	{
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	}
	else
	{
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	}

	SDL_RenderDrawLine(this->gRenderer, x1, y1, x2, y2);
#endif
	return;
}


void Renderer::PrintTextMini(const int& x, const int& y, const uString& s, const int& drawType) const
{
	if (x < 0 || x >= this->SCREEN_WIDTH)
	{
		return;
	}
	else if (y < 0 || y >= this->SCREEN_HEIGHT)
	{
		return;
	}

#if _MSC_VER == 1200
	if(s.GetLen() <= 0)
	{
		return;
	}
	PrintMini(x,y,s.GetText(),drawType);
#endif

#if _MSC_VER != 1200
	SDL_Color textColor;
	if (drawType == 0)
	{
		//black
		textColor.a = 255;
		textColor.r = 0;
		textColor.g = 0;
		textColor.b = 0;
	}
	else
	{
		//default (black)
		textColor.a = 255;
		textColor.r = 0;
		textColor.g = 0;
		textColor.b = 0;
	}

	if (s.GetLen() <= 0)
	{
		//nothing to be done
		return;
	}

	//I know its a sin to reload the text every frame but I wanted this to emulate the casio library
	SDL_Surface * loadedSurface = NULL;
	loadedSurface = TTF_RenderText_Solid(gFont, (char *)s.GetText(), textColor);
	if (!loadedSurface)
	{
		std::cout << "can not load text TTF error: " << TTF_GetError() << std::endl;
		return;
	}
	SDL_Texture * newTexture = NULL;
	newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	if (!newTexture)
	{
		std::cout << "can't make a texture from text SDL error: " << SDL_GetError() << std::endl;
		return;
	}
	int mWidth = loadedSurface->w;
	int mHeight = loadedSurface->h;

	SDL_Rect renderQuad = { x * (SCREEN_WIDTH / 127.0), y * (SCREEN_HEIGHT / 63.0), mWidth, mHeight }; //where to render on window

	//render to screen
	SDL_RenderCopyEx(gRenderer, newTexture, NULL, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);


	SDL_FreeSurface(loadedSurface);

	SDL_DestroyTexture(newTexture);

#endif
}

void Renderer::PrintTextXY(const int& x, const int& y, const uString& s, const int& drawType) const
{
	if (x < 0 || x >= this->SCREEN_WIDTH)
	{
		return;
	}
	else if (y < 0 || y >= this->SCREEN_HEIGHT)
	{
		return;
	}
#if _MSC_VER == 1200
	if (s.GetLen() <= 0)
	{
		return;
	}

	PrintXY(x,y,s.GetText(),drawType);
#endif

#if _MSC_VER != 1200
	SDL_Color textColor;

	if (drawType == 0)
	{
		//black
		textColor.a = 255;
		textColor.r = 0;
		textColor.g = 0;
		textColor.b = 0;
	}
	else if (drawType == 1)
	{
		//white
		textColor.a = 255;
		textColor.r = 255;
		textColor.g = 255;
		textColor.b = 255;
	}
	else
	{
		//default (black)
		textColor.a = 255;
		textColor.r = 0;
		textColor.g = 0;
		textColor.b = 0;
	}

	if (s.GetLen() <= 0)
	{
		//nothing to be done
		return;
	}

	//I know its a sin to reload the text every frame but I wanted this to emulate the casio library
	SDL_Surface * loadedSurface = NULL;
	loadedSurface = TTF_RenderText_Solid(gFont,(char *)s.GetText(), textColor);
	if (!loadedSurface)
	{
		std::cout << "can not load text TTF error: " << TTF_GetError() << std::endl;
		return;
	}
	SDL_Texture * newTexture = NULL;
	newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	if (!newTexture)
	{
		std::cout << "can't make a texture from text SDL error: " << SDL_GetError() << std::endl;
		return;
	}
	int mWidth = loadedSurface->w;
	int mHeight = loadedSurface->h;

	SDL_Rect renderQuad = { x * (SCREEN_WIDTH / 127.0), y * (SCREEN_HEIGHT / 63.0), mWidth, mHeight }; //where to render on window

	//render to screen
	SDL_RenderCopyEx(gRenderer, newTexture, NULL, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);


	SDL_FreeSurface(loadedSurface);

	SDL_DestroyTexture(newTexture);


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
#if _MSC_VER != 1200
	if (inverted == 0)
	{
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	}
	else
	{
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	}
	SDL_Rect fillRect;
	fillRect.x = x1* (SCREEN_WIDTH / 127.0);
	fillRect.y = y1* (SCREEN_HEIGHT / 63.0);
	fillRect.w = (x2 - x1)* (SCREEN_WIDTH / 127.0);
	fillRect.h = (y2 - y1)* (SCREEN_HEIGHT / 63.0);
	SDL_RenderFillRect(gRenderer, &fillRect);
#endif
}

void Renderer::ClearScreen() const
{
#if _MSC_VER != 1200
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
#endif
#if _MSC_VER == 1200
	Bdisp_AllClr_VRAM();
#endif
}

void Renderer::ClearScreen(Point topLeft, Point botRight) const
{
#if _MSC_VER != 1200
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	SDL_Rect viewBoundaries;

	viewBoundaries.x = topLeft.x * (SCREEN_WIDTH / 127.0);
	viewBoundaries.y = topLeft.y * (SCREEN_HEIGHT / 63.0);
	viewBoundaries.w = (botRight.x - topLeft.x) * (SCREEN_WIDTH / 127.0);
	viewBoundaries.h = (botRight.y - topLeft.y) * (SCREEN_HEIGHT / 63.0);

	SDL_RenderFillRect(gRenderer, &viewBoundaries);

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
#if _MSC_VER != 1200
	SDL_RenderPresent(gRenderer);
#endif
#if _MSC_VER == 1200
	Bdisp_PutDisp_DD();
#endif
}

Renderer::~Renderer()
{
#if _MSC_VER != 1200
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
#endif
}