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
	//total number of setting entries there are
	int NUMSETTINGS;
	
	int FirstSettingsNum;

	void DrawSettings();
public:
	//constructor
	VWindow(Renderer* gRenderer);

	bool Input();
	bool Proccess();
	void Display();

	Settings& GetSettings();
};

#endif