#include "GameStatus.h"

GameStatus::GameStatus(const int& width, const int& height, StateType mState) : gRenderer(width, height)
{
	this-> state = mState;

#if _MSC_VER == 1800
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "failed to open SDL video. SDL error: " << SDL_GetError() << std::endl;
		return;
	}

	gRenderer.gWindow = SDL_CreateWindow("3D Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, gRenderer.SCREEN_WIDTH, gRenderer.SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!gRenderer.gWindow)
	{
		std::cout << "can't create a window. SDL error: " << SDL_GetError() << std::endl;
		return;
	}

	gRenderer.gRenderer = SDL_CreateRenderer(gRenderer.gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!gRenderer.gRenderer)
	{
		std::cout << "can't create a renderer. SDL error: " << SDL_GetError() << std::endl;
		return;
	}
#endif

}