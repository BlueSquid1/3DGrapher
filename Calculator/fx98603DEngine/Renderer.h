#ifndef RENDERER_H
#define RENDERER_H

#ifndef NULL
	#define NULL 0
#endif


#if _MSC_VER == 1800
	#include <SDL.h>
	#include <SDL_ttf.h> //for rendering text to screen
#endif

#if _MSC_VER == 1200
extern "C"
{
	#include <fxlib.h>
}
#endif

#include "Mesh.h"
#include "Point.h"

class Renderer
{
	friend class Triangle; //so triangle objects can use draw line
public:

	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;

#if _MSC_VER == 1800
	SDL_Window * gWindow;
	SDL_Renderer * gRenderer;
	SDL_Event e;
	TTF_Font * gFont;
#endif
	//so curser knows how many pixels to jump
	int fontWidth;
	
	//so curser knows how heigh it should be
	int fontHeight;

	//constructor
	Renderer(const int& width, const int& height);

#if _MSC_VER == 1800
	bool SetColour(const Uint8& r, const Uint8& g, const Uint8& b, const Uint8& a);
#endif

	void DrawLine(int x1, int y1, int x2, int y2) const;
	
	//STILL NEED TO IMPLIMENT FOR SDL!!
	//drawType = 0 (overwrite)
	//drawType = 1 (OR)
	//drawType = 2 (Reverse colour)
	//drawType = 3 (Or in reverse colour)
	void PrintTextMini(const int& x, const int& y, const uString& s, const int& drawType) const;
	
	//drawType = 0 (black text)
	//drawType = 1 (white text)
	void PrintTextXY(const int& x, const int& y, const uString& s, const int& drawType) const;
	
	void DrawBox(const int& x1, const int& y1, const int& x2, const int& y2, bool inverted) const;
	
	void ClearScreen() const;
	
	//overload method ClearScreen()
	void ClearScreen(Point topLeft, Point botRight) const;
	
	void UpdateScreen() const;

	~Renderer();
};

#endif //GRAPHICS_H