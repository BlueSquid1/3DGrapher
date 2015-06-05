#include "VWindow.h"

void VWindow::DrawSettings()
{
	uString settingName[10];
	settingName[0] = "Xmin";
	settingName[1] = "Xmax";
	settingName[2] = "Ymin";
	settingName[3] = "Ymax";
	settingName[4] = "Zmin";
	settingName[5] = "Zmax";
	settingName[6] = "XRes";
	settingName[7] = "YRes";
	settingName[8] = "Yaw";
	settingName[9] = "Pitch";

	//workout which setting is at the top
	int startPos = 0;
	if (curserPos - 2 > 0)
	{
		//when approaching end limit the startPos
		if (curserPos + 3 >= NUMSETTINGS)
		{
			startPos = NUMSETTINGS - 6;
		}
		else
		{
			startPos = curserPos - 2;
		}
	}
	else
	{
		//near start of list
		startPos = 0;
	}

	//can only display six settings at once
	int counter = 0;
	for (int i = startPos; i < startPos + 6; i++)
	{
		//make sure to stick inside the boundaries
		if (i < NUMSETTINGS)
		{
			//draw a black box where the selector is
			if (i == this->curserPos)
			{
				gRenderer->DrawBox(0, (counter + 1) * 8, 127, (counter + 1) * 8 + 8, 0);
			}

			gRenderer->PrintTextXY(0, (counter + 1) * 8, settingName[i], i == this->curserPos);
		}
		counter++;
	}

}


VWindow::VWindow(Renderer* gRenderer) : GameStatus(gRenderer, VWINDOW)
{
	//set initial settings
	graphSettings.xMin = -3;
	graphSettings.xMax = 3;
	graphSettings.xGridRes = 10;
	graphSettings.yMin = -3;
	graphSettings.yMax = 3;
	graphSettings.yGridRes = 10;
	graphSettings.zMin = -3;
	graphSettings.zMax = 3;

	graphSettings.yawAngle = 0.0;
	graphSettings.pitchAngle = 0.0;


	curserPos = 0;
	NUMSETTINGS = 10;
}


bool VWindow::Input()
{
#if _MSC_VER == 1800
	while (SDL_PollEvent(&gRenderer->e) != 0)
	{
		if (gRenderer->e.type == SDL_QUIT)
		{
			this->nextState = QUIT;
			return false;
		}
		else if (gRenderer->e.type == SDL_KEYDOWN)
		{
			switch (gRenderer->e.key.keysym.sym)
			{
			case SDLK_RIGHT:
				this->nextState = EDITTEXT;
				return false;
				break;

			case SDLK_LEFT:

				break;

			case SDLK_UP:
			{
				curserPos--;
				break;
			}
			case SDLK_DOWN:
			{
				curserPos++;
				break;
			}

			case SDLK_EQUALS:
			{

				break;
			}

			case SDLK_ESCAPE:
			{
				this->nextState = MAINMENU;
				return false;
				break;
			}

			default:
				break;
			}
		}
	}
#endif

#if _MSC_VER == 1200
	unsigned int key;
	GetKey(&key);

	switch (key)
	{
	case KEY_CTRL_RIGHT:
		this->nextState = EDITTEXT;
		return false;
		break;
	case KEY_CTRL_LEFT:

		break;

	case KEY_CTRL_UP:
	{
		curserPos--;
		break;
	}
	case KEY_CTRL_DOWN:
	{
		curserPos++;
		break;
	}
	default:
	{
		//if its none of the special case keys then edit the text
		this->nextState = EDITTEXT;
		return false;
		break;
	}
	}
#endif
	return true;
}

bool VWindow::Proccess()
{
	if (curserPos < 0)
	{
		curserPos = 0;
	}
	else if (curserPos >= NUMSETTINGS)
	{
		curserPos = NUMSETTINGS - 1;
	}
	return true;
}

void VWindow::Display()
{
	gRenderer->ClearScreen();
	//draw title
	uString title = "View Window";
	gRenderer->PrintTextXY(0, 0, title, 0);

	//draw setting fields
	this->DrawSettings();

	gRenderer->UpdateScreen();
}


GraphData VWindow::GetSettings()
{
	return graphSettings;
}