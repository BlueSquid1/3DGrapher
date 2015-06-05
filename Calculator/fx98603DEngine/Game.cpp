#include "Game.h"


Game::Game(const int& widthRes, const int& heightRes) : gRenderer(widthRes, heightRes), Engine3D(&gRenderer), MainMenu(&gRenderer), EditText(&gRenderer), ViewWindow(&gRenderer)
{
	currentState = &MainMenu;
}


bool Game::UpdateCurrentState()
{
	StateType from = currentState->state;
	StateType destiny = currentState->nextState;

	if (from == MAINMENU && destiny == GRAPHER)
	{
		//get function data from menu
		Function* funcs = MainMenu.GetFunctions();

		//create a pointer to the view settings data (for easy access)
		//GraphData * viewData = &ViewWindow.GetSettings();
		ViewWindow.GetSettings();

		//update the grids for each function
		int minX = ViewWindow.GetSettings().xMin;
		int minY = ViewWindow.GetSettings().yMin;
		int minZ = ViewWindow.GetSettings().zMin;
		Vector min(minX, minY, minZ);

		int maxX = ViewWindow.GetSettings().xMax;
		int maxY = ViewWindow.GetSettings().yMax;
		int maxZ = ViewWindow.GetSettings().zMax;

		Vector max(maxX, maxY, maxZ);

		for (int i = 0; i < 6; i++)
		{
			if (funcs[i].IsDrawable())
			{
				funcs[i].SetGridRes(ViewWindow.GetSettings().xGridRes, ViewWindow.GetSettings().yGridRes);
				funcs[i].UpdateGrid(min, max);
			}
		}

		//load the functions
		Engine3D.LoadFunctions(funcs);

		//reset the camera
		Engine3D.Reset();

		currentState = &Engine3D;

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
	else if (from == MAINMENU && destiny == VWINDOW)
	{
		currentState = &ViewWindow;
	}
	else if (from == GRAPHER && destiny == MAINMENU)
	{

		currentState = &MainMenu;
	}
	else if (from == EDITTEXT && destiny == MAINMENU)
	{
		uString text = EditText.GetText();

		MainMenu.SetCurrentFunction(text);
		currentState = &MainMenu;
	}
	else if (from == VWINDOW && destiny == MAINMENU)
	{
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
	currentState->Proccess();

	currentState->Display();

	//ideally would do input first but the casio library pauses the program until user input
	bool mContinue = currentState->Input();

	return mContinue;
}