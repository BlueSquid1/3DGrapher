#ifndef VWINDOW_H
#define VWINDOW_H

#include "GameStatus.h"
#include "uString.h"

//storage place for grapher settings
struct GraphData
{
	int xMin;
	int xMax;
	int xGridRes;
	int yMin;
	int yMax;
	int yGridRes;
	int zMin;
	int zMax;

	float yawAngle;
	float pitchAngle;
};


//View Window state
class VWindow : public GameStatus
{
	GraphData graphSettings;

	//curser points to the current setting
	int curserPos;
	int NUMSETTINGS;


	void DrawSettings();
public:
	//constructor
	VWindow(Renderer* gRenderer);

	bool Input();
	bool Proccess();
	void Display();

	GraphData GetSettings();
};

#endif