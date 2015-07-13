#include "..\..\..\Calculator\fx98603DEngine\Game.h"

#include <iostream>


int main(int argc, char* args[])
{

	//change resolution of application here
	Game application(800, 600);

	bool quit = false;
	while (!quit)
	{

		application.UpdateCurrentState();

		bool mContinue = true;
		while (mContinue == true)
		{
			mContinue = application.RunCurrentState();
		}


		if (application.currentState->nextState == QUIT)
		{
			quit = true;
		}

	}
	return 0;
}