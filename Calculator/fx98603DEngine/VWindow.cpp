#include "VWindow.h"

void VWindow::DrawSettings()
{

	//draw a box where the selector is
	int yPos = (curserPos - FirstSettingsNum + 1) * 8;
	gRenderer->DrawBox(0, yPos, 127, yPos + 8, 0);

	//print a text seperator for each line
	for (int i = 0; i < 6; i++)
	{
		gRenderer->PrintTextXY(6 * 5, (i + 1) * 8, ":", curserPos == FirstSettingsNum + i);
	}

	//print data and text
	//keep track of how many variables displayed
	int counter = 0;
	char s[10];

	switch (FirstSettingsNum)
	{
	case 0:
		gRenderer->PrintTextXY(0, (counter + 1) * 8, "Xmin", curserPos == counter + FirstSettingsNum);
		sprintf(s, "%d", grapherSettings.xMin);
		gRenderer->PrintTextXY(35, (counter + 1) * 8, s, curserPos == counter + FirstSettingsNum);
		counter++;

	case 1:
		gRenderer->PrintTextXY(0, (counter + 1) * 8, "Xmax", curserPos == counter + FirstSettingsNum);
		sprintf(s, "%d", grapherSettings.xMax);
		gRenderer->PrintTextXY(35, (counter + 1) * 8, s, curserPos == counter + FirstSettingsNum);
		counter++;

	case 2:
		gRenderer->PrintTextXY(0, (counter + 1) * 8, "Ymin", curserPos == counter + FirstSettingsNum);
		sprintf(s, "%d", grapherSettings.yMin);
		gRenderer->PrintTextXY(35, (counter + 1) * 8, s, curserPos == counter + FirstSettingsNum);
		counter++;

	case 3:
		gRenderer->PrintTextXY(0, (counter + 1) * 8, "Ymax", curserPos == counter + FirstSettingsNum);
		sprintf(s, "%d", grapherSettings.yMax);
		gRenderer->PrintTextXY(35, (counter + 1) * 8, s, curserPos == counter + FirstSettingsNum);
		counter++;

	case 4:
		gRenderer->PrintTextXY(0, (counter + 1) * 8, "Zmin", curserPos == counter + FirstSettingsNum);
		sprintf(s, "%d", grapherSettings.zMin);
		gRenderer->PrintTextXY(35, (counter + 1) * 8, s, curserPos == counter + FirstSettingsNum);
		counter++;

	case 5:
		gRenderer->PrintTextXY(0, (counter + 1) * 8, "Zmax", curserPos == counter + FirstSettingsNum);
		sprintf(s, "%d", grapherSettings.zMax);
		gRenderer->PrintTextXY(35, (counter + 1) * 8, s, curserPos == counter + FirstSettingsNum);
		counter++;

	case 6:
		gRenderer->PrintTextXY(0, (counter + 1) * 8, "XRes", curserPos == counter + FirstSettingsNum);
		sprintf(s, "%d", grapherSettings.xGridRes);
		gRenderer->PrintTextXY(35, (counter + 1) * 8, s, curserPos == counter + FirstSettingsNum);
		counter++;

	case 7:
		gRenderer->PrintTextXY(0, (counter + 1) * 8, "YRes", curserPos == counter + FirstSettingsNum);
		sprintf(s, "%d", grapherSettings.yGridRes);
		gRenderer->PrintTextXY(35, (counter + 1) * 8, s, curserPos == counter + FirstSettingsNum);
		counter++;

	case 8:
		gRenderer->PrintTextXY(0, (counter + 1) * 8, "Yaw", curserPos == counter + FirstSettingsNum);
		sprintf(s, "%f", grapherSettings.yawAngle);
		gRenderer->PrintTextXY(35, (counter + 1) * 8, s, curserPos == counter + FirstSettingsNum);
		counter++;

	case 9:
		gRenderer->PrintTextXY(0, (counter + 1) * 8, "Pitch", curserPos == counter + FirstSettingsNum);
		sprintf(s, "%f", grapherSettings.pitchAngle);
		gRenderer->PrintTextXY(35, (counter + 1) * 8, s, curserPos == counter + FirstSettingsNum);
		counter++;
	}
}


VWindow::VWindow(Renderer* gRenderer) : GameStatus(gRenderer, VWINDOW)
{
	//set initial settings
	grapherSettings.xMin = -3;
	grapherSettings.xMax = 3;
	grapherSettings.xGridRes = 10;
	grapherSettings.yMin = -3;
	grapherSettings.yMax = 3;
	grapherSettings.yGridRes = 10;
	grapherSettings.zMin = -3;
	grapherSettings.zMax = 3;

	grapherSettings.yawAngle = 0.0;
	grapherSettings.pitchAngle = 0.0;


	curserPos = 0;
	NUMSETTINGS = 10;
	FirstSettingsNum = 0;
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
	
	
	//workout which setting is at the top
	if (curserPos - 2 > 0)
	{
		//when approaching end limit the FirstSettingsNum
		if (curserPos + 3 >= NUMSETTINGS)
		{
			FirstSettingsNum = NUMSETTINGS - 6;
		}
		else
		{
			FirstSettingsNum = curserPos - 2;
		}
	}
	else
	{
		//near start of list
		FirstSettingsNum = 0;
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


Settings& VWindow::GetSettings()
{
	return grapherSettings;
}