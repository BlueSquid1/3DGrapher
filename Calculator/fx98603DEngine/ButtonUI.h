#ifndef BUTTONUI_H
#define BUTTONUI_H

#define BUTTON_WIDTH 20
#define BUTTON_HEIGHT 7



#include "Point.h"
#include "ustring.h"

#include "Renderer.h"

class ButtonUI
{
	//stores the topleft corner of the button
	Point mPosition;

	int width;
	int height;

	uString title;

public:
	//constructor
	ButtonUI();

	bool SetPos(int x, int y, int mWidth = -1, int mHeight = -1);
	bool SetText(const uString& mTitle);

#if _MSC_VER == 1200
	bool HandleEvent(unsigned int * e);
#endif
#if _MSC_VER != 1200
	bool HandleEvent(SDL_Event * e);
#endif
	void Render(Renderer * gRenderer, int mX = -1, int mY = -1);

};

#endif