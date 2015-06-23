#ifndef VWINDOW_H
#define VWINDOW_H

#include "GameStatus.h"
#include "uString.h"

//storage place for grapher settings
struct Settings
{
	//view window boundaries
	int xMin;
	int xMax;
	int yMin;
	int yMax;
	int zMin;
	int zMax;

	//functions resolution
	int xGridRes;
	int yGridRes;

	//camera angle
	float yawAngle;
	float pitchAngle;
};


//View Window state
class VWindow : public GameStatus
{
	Settings grapherSettings;
	//curser points to the current setting
	int curserPos;

	//only for display purposes
	//---
	//total number of setting entries there are
	int NUMSETTINGS;
	//setting that should be printed at the top of the list
	int FirstSettingsNum;
	//the element to print next
	int counter;
	//print an integer setting (returns false if no more space left to print settings)
	bool PrintSetting(int value, uString title);

	//print a float setting (returns false if no more space left to print settings)
	bool PrintSetting(float value, uString title);
	//prints all visiable settings
	void DrawSettings();
	//===
public:
	//constructor
	VWindow(Renderer* gRenderer);

	bool Input();
	bool Proccess();
	void Display();

	Settings& GetSettings();

	int GetCurserPos();
};

#endif