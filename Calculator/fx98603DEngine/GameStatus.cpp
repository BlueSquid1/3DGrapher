#include "GameStatus.h"


GameStatus::GameStatus(Renderer* origRenderer, StateType mState)
{
	this-> state = mState;
	this->nextState = QUIT;
	gRenderer = origRenderer;
}