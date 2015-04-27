#include "GameStatus.h"


bool GameStatus::UpdateState(GameStatus * currentState)
{
	return true;
}


GameStatus::GameStatus(Renderer* origRenderer, StateType mState)
{
	this-> state = mState;
	gRenderer = origRenderer;
}