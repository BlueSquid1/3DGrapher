#ifndef VWINDOW_H
#define VWINDOW_H

#include "GameStatus.h"
#include "uString.h"

//storage place for grapher settings
enum
{
	xMin,
	xMax,
	yMin,
	yMax,
	zMin,
	zMax,
	xGridRes,
	yGridRes,

	yawAngle,
	pitchAngle,
};


//View Window state
class VWindow : public GameStatus
{
	float settingsData[10];

	//curser points to the current setting
	int curserPos;
	int NUMSETTINGS;
	
	int FirstSettingsNum;

	void DrawSettings();
public:
	//constructor
	VWindow(Renderer* gRenderer);

	bool Input();
	bool Proccess();
	void Display();

	float* GetSettings();
};

#endif