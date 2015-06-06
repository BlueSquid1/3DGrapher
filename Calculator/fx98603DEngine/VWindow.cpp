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

	//can only display six settings at once
	int counter = 0;
	for (int i = FirstSettingsNum; i < FirstSettingsNum + 6; i++)
	{
		//make sure to stick inside the boundaries
		if (i < NUMSETTINGS && i >= 0)
		{
			//remember how many pixel down on the y axis the next line is
			int yPixels = (counter + 1) * 8;
			//draw a black box where the selector is
			if (i == this->curserPos)
			{
				gRenderer->DrawBox(0, yPixels, 127, (counter + 1) * 8 + 8, 0);
			}
			
			//print title
			gRenderer->PrintTextXY(0, yPixels, settingName[i], i == this->curserPos);
			
			//print seperator
			uString spacer = ":";
			gRenderer->PrintTextXY(gRenderer->fontWidth * 8, yPixels, spacer, i == this->curserPos);
			
			//print value
			char s[15];
			sprintf(s, "%f", this->settingsData[i]);
			uString dataValue = s;

			gRenderer->PrintTextXY(gRenderer->fontWidth * 9, yPixels, dataValue, i == this->curserPos);

		}
		else
		{
			uString::ErrorPrint("trying to display a setting that is out of the setting list");
		}
		counter++;
	}

}


VWindow::VWindow(Renderer* gRenderer) : GameStatus(gRenderer, VWINDOW)
{
	//set initial settings
	settingsData[xMin] = -3;
	settingsData[xMax] = 3;
	settingsData[xGridRes] = 10;
	settingsData[yMin] = -3;
	settingsData[yMax] = 3;
	settingsData[yGridRes] = 10;
	settingsData[zMin] = -3;
	settingsData[zMax] = 3;

	settingsData[yawAngle] = 0.0;
	settingsData[pitchAngle] = 0.0;


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


float* VWindow::GetSettings()
{
	return settingsData;
}