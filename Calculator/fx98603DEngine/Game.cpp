#include "Game.h"


Game::Game(const int& widthRes, const int& heightRes) : gRenderer(widthRes, heightRes), Engine3D(&gRenderer), MainMenu(&gRenderer), EditText(&gRenderer)
{
	currentState = &MainMenu;
}


bool Game::UpdateCurrentState()
{
	StateType from = currentState->state;
	StateType destiny = currentState->nextState;

	if (from == MAINMENU && destiny == GRAPHER)
	{
		/*
		Function eq;

		uString equationS = "X^2-Y^2";

		eq.SetEquation(equationS);

		eq.SetDrawable(true);

		eq.SetGridRes(10, 10);

		Vector min(-3,-3,-3);
		Vector max(3, 3, 3);

		eq.UpdateGrid(min, max);

		Engine3D.LoadFunction(&eq);
		*/
	}
	else if (from == MAINMENU && destiny == EDITTEXT)
	{
		int funcNum = MainMenu.GetFuncNum();
		uString text = MainMenu.CurrentString();

		Point TL;
		TL.x = 18;
		TL.y = (funcNum + 1) * 8;

		Point BR;
		BR.x = 127;
		BR.y = TL.y + 8;

		EditText.LoadTextAndPos(text, TL, BR);

		currentState = &EditText;
	}
	else if (from == GRAPHER && destiny == MAINMENU)
	{

	}
	else if (from == EDITTEXT && destiny == MAINMENU)
	{
		uString text = EditText.GetText();

		MainMenu.SetCurrentFunction(text);
		currentState = &MainMenu;
	}
	else
	{
		//do nothing
	}

	return true;
}



bool Game::RunCurrentState()
{
	bool mContinue = currentState->Input();

	currentState->Proccess();

	currentState->Display();

	return mContinue;
}