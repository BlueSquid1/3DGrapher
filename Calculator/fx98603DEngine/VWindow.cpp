#include "VWindow.h"

bool VWindow::PrintSetting(int value, uString title)
{
	char s[10];
	gRenderer->PrintTextXY(0, (this->counter + 1) * 8, title, this->curserPos == this->counter + this->FirstSettingsNum);
	sprintf(s, "%d", value);
	gRenderer->PrintTextXY(35, (this->counter + 1) * 8, s, this->curserPos == this->counter + this->FirstSettingsNum);
	this->counter++;

	//return false if can't fit any more settings entries on the screen
	const int MAXNUMOFSETTINGS = 6;
	if (this->counter >= MAXNUMOFSETTINGS)
	{
		return false;
	}
	return true;
}

bool VWindow::PrintSetting(float value, uString title)
{
	char s[10];
	gRenderer->PrintTextXY(0, (this->counter + 1) * 8, title, this->curserPos == this->counter + this->FirstSettingsNum);
	sprintf(s, "%f", value);
	gRenderer->PrintTextXY(35, (this->counter + 1) * 8, s, this->curserPos == this->counter + this->FirstSettingsNum);
	this->counter++;

	//return false if can't fit any more settings entries on the screen
	const int MAXNUMOFSETTINGS = 6;
	if (this->counter >= MAXNUMOFSETTINGS)
	{
		return false;
	}
	return true;
}

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
	this->counter = 0;

	switch (FirstSettingsNum)
	{
	case 0:
		if (!PrintSetting(grapherSettings.xMin, "Xmin"))
		{
			break;
		}

	case 1:
		if (!PrintSetting(grapherSettings.xMax, "Xmax"))
		{
			break;
		}

	case 2:
		if (!PrintSetting(grapherSettings.yMin, "Ymin"))
		{
			break;
		}

	case 3:
		if (!PrintSetting(grapherSettings.yMax, "Ymax"))
		{
			break;
		}

	case 4:
		if (!PrintSetting(grapherSettings.zMin, "Zmin"))
		{
			break;
		}

	case 5:
		if (!PrintSetting(grapherSettings.zMax, "Zmax"))
		{
			break;
		}

	case 6:
		if (!PrintSetting(grapherSettings.xGridRes, "XRes"))
		{
			break;
		}

	case 7:
		if (!PrintSetting(grapherSettings.yGridRes, "YRes"))
		{
			break;
		}

	case 8:
		if (!PrintSetting(grapherSettings.yawAngle, "Yaw"))
		{
			break;
		}

	case 9:
		if (!PrintSetting(grapherSettings.pitchAngle, "Pitch"))
		{
			break;
		}
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

int VWindow::GetCurserPos()
{
	return this->curserPos;
}