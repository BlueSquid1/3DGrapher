#include "ButtonUI.h"


ButtonUI::ButtonUI()
{
	this->width = BUTTON_WIDTH;
	this->height = BUTTON_HEIGHT;
	this->mPosition.x = 0;
	this->mPosition.y = 0;

	//uString handles its own initalization
}

bool ButtonUI::SetPos(int x, int y, int mWidth, int mHeight)
{
	//check position entered
	if (x < 0 || y < 0)
	{
		uString::ErrorPrint("Position of text is invalid");
		return false;
	}

	this->mPosition.x = x;
	this->mPosition.y = y;

	//check if mWidth or mHeight are valid
	if (mWidth < 0 || mHeight < 0)
	{
		//not an error because will use default values instead
		return true;
	}

	mWidth = this->width;
	mHeight = this->height;

	return true;
}

bool ButtonUI::SetText(const uString& mTitle)
{
	this->title = mTitle;
	return true;
}

#if _MSC_VER == 1200
bool ButtonUI::HandleEvent(unsigned int * e)
{
	return true;
}
#endif

#if _MSC_VER == 1800
bool ButtonUI::HandleEvent(SDL_Event * e)
{
	return true;
}
#endif


void ButtonUI::Render(Renderer *gRenderer, int mX, int mY)
{
	//update position if needed
	if (mX >= 0 && mY >= 0)
	{
		this->mPosition.x = mX;
		this->mPosition.y = mY;
	}

	int leftX = this->mPosition.x;
	int topY = this->mPosition.y;

	int rightX = leftX + this->width;
	int botY = topY + this->height;

	//draw a box
	gRenderer->DrawBox(leftX, topY, rightX, botY, 0);
	gRenderer->DrawBox(leftX + 1, topY + 1, rightX, botY, 1);

	//draw the triangle

	//draw the text
	int spacerX = 3;
	//int spacerX = (this->width - gRenderer->fontWidth * title.GetLen()) / 2.0;
	int spacerY = 2;
	gRenderer->PrintTextMini(leftX + spacerX, topY + spacerY, this->title, 0);
}