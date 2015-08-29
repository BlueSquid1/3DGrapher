#include "VWindow.h"

bool VWindow::PrintSetting(int value, const uString& title)
{
	char s[20];
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

bool VWindow::PrintSetting(float value, const uString& title)
{
	char s[20];
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

bool VWindow::PrintSetting(bool value, const uString& title)
{
	char s[20];
	gRenderer->PrintTextXY(0, (this->counter + 1) * 8, title, this->curserPos == this->counter + this->FirstSettingsNum);
	
	if (value)
	{
		sprintf(s, "True");
	}
	else
	{
		sprintf(s, "False");
	}
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

	//I am using blender's orientation therefore the x axis is the y axis and vias versia
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
		if (!PrintSetting(grapherSettings.xGridRes, "XRes"))
		{
			break;
		}

	case 5:
		if (!PrintSetting(grapherSettings.yGridRes, "YRes"))
		{
			break;
		}

	case 6:
		if (!PrintSetting(grapherSettings.xScaling, "XScal"))
		{
			break;
		}

	case 7:
		if (!PrintSetting(grapherSettings.yScaling, "YScal"))
		{
			break;
		}
	case 8:
		if (!PrintSetting(grapherSettings.zScaling, "ZScal"))
		{
			break;
		}

	case 9:
		if (!PrintSetting(grapherSettings.yawAngle, "Yaw"))
		{
			break;
		}

	case 10:
		if (!PrintSetting(grapherSettings.pitchAngle, "Pitch"))
		{
			break;
		}
	case 11:
		if (!PrintSetting(grapherSettings.xCameraPos, "Xcam"))
		{
			break;
		}
	case 12:
		if (!PrintSetting(grapherSettings.yCameraPos, "Ycam"))
		{
			break;
		}
	case 13:
		if (!PrintSetting(grapherSettings.zCameraPos, "Zcam"))
		{
			break;
		}
	case 14:
		if (!PrintSetting(grapherSettings.useTriangleMesh, "Ngon"))
		{
			break;
		}
	case 15:
		if (!PrintSetting(grapherSettings.SolidMesh, "Solid"))
		{
			break;
		}
	case 16:
		if (!PrintSetting(grapherSettings.DisplayAxes, "Axes"))
		{
			break;
		}
	}
}

#if _MSC_VER != 1200
uString VWindow::TextInput(SDL_Event * e)
{
	//gather where to edit text
	uString text = this->GetCurrentDataString();

	Point TL;
	TL.x = 35;
	TL.y = this->GetCurserYPos();

	Point BR;
	BR.x = 127;
	BR.y = TL.y + 8;

	//initalize edit text object
	EditTextState EditText(this->gRenderer);

	//clear text if its not moving curser
	if (!e->key.keysym.sym == SDLK_RIGHT)
	{
		text = "";
	}

	EditText.LoadTextAndPos(text, TL, BR);

	//proccess previous text input
	EditText.proccessAInput(e);

	//enter text input mode
	bool mContinue = true;
	while (mContinue == true)
	{
		EditText.Proccess();

		EditText.Display();

		//ideally would do input first but the casio library pauses the program until user input
		mContinue = EditText.Input();
	}

	//leave text input mode
	return EditText.GetText();
}
#endif

#if _MSC_VER == 1200
uString VWindow::TextInput(unsigned int * key)
{
	//gather where to edit text
	uString text = this->GetCurrentDataString();

	Point TL;
	TL.x = 35;
	TL.y = this->GetCurserYPos();

	Point BR;
	BR.x = 127;
	BR.y = TL.y + 8;

	//initalize edit text object
	EditTextState EditText(this->gRenderer);


	if (!(*key == KEY_CTRL_RIGHT))
	{
		text = "";
	}

	EditText.LoadTextAndPos(text, TL, BR);

	//proccess previous text input
	EditText.proccessAInput(key);

	//enter text input mode
	bool mContinue = true;
	while (mContinue == true)
	{
		EditText.Proccess();

		EditText.Display();

		//ideally would do input first but the casio library pauses the program until user input
		mContinue = EditText.Input();
	}

	//leave text input mode
	return EditText.GetText();
}
#endif


bool VWindow::setCurrentValue(uString sValue)
{
	//first check the size
	if (sValue.GetLen() <= 0)
	{
		//don't override current value
		return false;
	}

	switch (this->curserPos)
	{
	case 0:
		grapherSettings.xMin = uString::ConvertToFloat(sValue);
		break;
	case 1:
		grapherSettings.xMax = uString::ConvertToFloat(sValue);
		break;
	case 2:
		grapherSettings.yMin = uString::ConvertToFloat(sValue);
		break;
	case 3:
		grapherSettings.yMax = uString::ConvertToFloat(sValue);
		break;
	case 4:
		grapherSettings.xGridRes = uString::ConvertToInt(sValue);
		break;
	case 5:
		grapherSettings.yGridRes = uString::ConvertToInt(sValue);
		break;
	case 6:
		grapherSettings.xScaling = uString::ConvertToFloat(sValue);
		break;
	case 7:
		grapherSettings.yScaling = uString::ConvertToFloat(sValue);
		break;
	case 8:
		grapherSettings.zScaling = uString::ConvertToFloat(sValue);
		break;
	case 9:
		grapherSettings.yawAngle = uString::ConvertToFloat(sValue);
		break;
	case 10:
		grapherSettings.pitchAngle = uString::ConvertToFloat(sValue);
		break;
	case 11:
		grapherSettings.xCameraPos = uString::ConvertToFloat(sValue);
		break;
	case 12:
		grapherSettings.yCameraPos = uString::ConvertToFloat(sValue);
		break;
	case 13:
		grapherSettings.zCameraPos = uString::ConvertToFloat(sValue);
		break;
	case 14:
		grapherSettings.useTriangleMesh = uString::ConvertToInt(sValue);
		break;
	case 15:
		grapherSettings.SolidMesh = uString::ConvertToInt(sValue);
		break;
	case 16:
		grapherSettings.DisplayAxes = uString::ConvertToInt(sValue);
	}

}

bool VWindow::VWindowChecks()
{
	if (grapherSettings.xMin >= grapherSettings.xMax)
	{
		uString::ErrorPrint("Xmin has to be below Xmax");
		return false;
	}
	else if (grapherSettings.yMin >= grapherSettings.yMax)
	{
		uString::ErrorPrint("Ymin has to be below Ymax");
	}
	else if (grapherSettings.xGridRes < 1)
	{
		uString::ErrorPrint("Xres must be greater than 0");
	}
	else if (grapherSettings.xGridRes > 50)
	{
		uString::ErrorPrint("Xres value is too high");
	}
	else if (grapherSettings.yGridRes < 1)
	{
		uString::ErrorPrint("Yres must be greater than 0");
	}
	else if (grapherSettings.yGridRes > 50)
	{
		uString::ErrorPrint("Yres value is too high");
	}
	else
	{
		//Values are all approrate
		return true;
	}

	return false;
}


VWindow::VWindow(Renderer* gRenderer) : GameStatus(gRenderer, VWINDOW)
{
	//set initial settings
	grapherSettings.xMin = -3.0;
	grapherSettings.xMax = 3.0;
	grapherSettings.xGridRes = 10;
	grapherSettings.yMin = -3.0;
	grapherSettings.yMax = 3.0;
	grapherSettings.yGridRes = 10;

	grapherSettings.xScaling = 1.0;
	grapherSettings.yScaling = 1.0;
	grapherSettings.zScaling = 1.0;

	grapherSettings.yawAngle = 0.0;
	grapherSettings.pitchAngle = 45.0;

	grapherSettings.xCameraPos = 0.0;
	grapherSettings.yCameraPos = 0.0;
	grapherSettings.zCameraPos = 0.0;

	grapherSettings.useTriangleMesh = true;
	grapherSettings.SolidMesh = false;
	grapherSettings.DisplayAxes = true;

	curserPos = 0;
	NUMSETTINGS = 17;
	FirstSettingsNum = 0;
}


bool VWindow::Input()
{
#if _MSC_VER != 1200
	while (SDL_PollEvent(&gRenderer->e) != 0)
	{
		if (gRenderer->e.type == SDL_QUIT)
		{
			//check to see if everything is valid
			this->nextState = QUIT;
			return false;
		}
		else if (gRenderer->e.type == SDL_KEYDOWN)
		{
			switch (gRenderer->e.key.keysym.sym)
			{
			case SDLK_RIGHT:
			{
				uString text = TextInput(&gRenderer->e);
				setCurrentValue(text);
				break;
			}
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
				//check setting variables to make sure they are valid
				if (this->VWindowChecks())
				{
					this->nextState = MAINMENU;
					return false;
				}
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
	case KEY_CTRL_EXIT:
		//check to see if everything is valid
		if (this->VWindowChecks())
		{
			this->nextState = MAINMENU;
			return false;
		}
		break;
	case KEY_CTRL_RIGHT:
	{
		uString text = TextInput(&key);
		setCurrentValue(text);
		break;
	}

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
		uString text = TextInput(&key);
		setCurrentValue(text);
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

int VWindow::GetCurserYPos()
{
	return 8 * (this->curserPos - this->FirstSettingsNum + 1);
}

uString VWindow::GetCurrentDataString()
{
	char s[20];
	switch (this->curserPos)
	{
	case 0:
		sprintf(s, "%f", grapherSettings.xMin);
		return s;
	case 1:
		sprintf(s, "%f", grapherSettings.xMax);
		return s;
	case 2:
		sprintf(s, "%f", grapherSettings.yMin);
		return s;
	case 3:
		sprintf(s, "%f", grapherSettings.yMax);
		return s;
	case 4:
		sprintf(s, "%d", grapherSettings.xGridRes);
		return s;
	case 5:
		sprintf(s, "%d", grapherSettings.yGridRes);
		return s;
	case 6:
		sprintf(s, "%f", grapherSettings.xScaling);
		return s;
	case 7:
		sprintf(s, "%f", grapherSettings.yScaling);
		return s;
	case 8:
		sprintf(s, "%f", grapherSettings.zScaling);
		return s;
	case 9:
		sprintf(s, "%f", grapherSettings.yawAngle);
		return s;
	case 10:
		sprintf(s, "%f", grapherSettings.pitchAngle);
		return s;
	case 11:
		sprintf(s, "%f", grapherSettings.xCameraPos);
		return s;
	case 12:
		sprintf(s, "%f", grapherSettings.yCameraPos);
		return s;
	case 13:
		sprintf(s, "%f", grapherSettings.zCameraPos);
		return s;
	case 14:
		sprintf(s, "%d", grapherSettings.useTriangleMesh);
		return s;
	case 15:
		sprintf(s, "%d", grapherSettings.SolidMesh);
		return s;
	case 16:
		sprintf(s, "%d", grapherSettings.DisplayAxes);
		return s;
	}
}