#include "GameStatus.h"


GameStatus::GameStatus(Renderer* origRenderer, StateType mState)
{
	this-> state = mState;
	gRenderer = origRenderer;
}