#include "Grapher.h"


Grapher::Grapher(Renderer* origRenderer) : GameStatus(origRenderer, GRAPHER)
{
}

bool Grapher::LoadFunction(Function* equation)
{
	this->func = equation;
	return true;
}

bool Grapher::Input()
{
#if _MSC_VER == 1800
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			this->nextState = QUIT;
			return false;
		}
		else if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_RIGHT:
				cam.Rotate(0, 0, -5);
				break;

			case SDLK_LEFT:
				cam.Rotate(0, 0, 5);
				break;

			case SDLK_UP:
			{
				float zAng = cam.GetRotHist()(2);
				zAng = zAng * (3.14159265 / 180.0);
				cam.Rotate(5 * cos(zAng), 5 * sin(zAng), 0);
				break;
			}
			case SDLK_DOWN:
			{
				float zAng = cam.GetRotHist()(2);
				zAng = zAng * (3.14159265 / 180.0);
				cam.Rotate(-5 * cos(zAng), -5 * sin(zAng), 0);
				break;
			}
			
			case SDLK_EQUALS:
			{
				float per = 0.95;
				cam.Zoom(per);
				break;
			}

			case SDLK_MINUS:
			{
				float per = 1.05;
				cam.Zoom(per);
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
		cam.Rotate(0, 0, -5);
		break;
	case KEY_CTRL_LEFT:
		cam.Rotate(0, 0, 5);
		break;

	case KEY_CTRL_UP:
	{
		float zAng = cam.GetRotHist()(2);
		zAng = zAng * (3.14159265 / 180.0);
		cam.Rotate(5 * cos(zAng), 5 * sin(zAng), 0);
		break;
	}
	case KEY_CTRL_DOWN:
	{
		float zAng = cam.GetRotHist()(2);
		zAng = zAng * (3.14159265 / 180.0);
		cam.Rotate(-5 * cos(zAng), -5 * sin(zAng), 0);
		break;
	}
			
	case KEY_CHAR_PLUS:
	{
		float per = 0.95;
		cam.Zoom(per);
		break;
	}
		
	case KEY_CHAR_MINUS:
	{
		float per = 1.05;
		cam.Zoom(per);
		break;
	}

	default:
		break;
	}
#endif
	return true;
}

bool Grapher::Proccess()
{
	
	for (int i = 0; i < func->GetObject().GetPixelstCount(); i++)
	{
		func->GetObject().GetPixel(i) = cam.Project3Dto2D(func->GetObject().GetVertex(i), gRenderer->SCREEN_WIDTH, gRenderer->SCREEN_HEIGHT);
	}
	
	return true;
}

void Grapher::Display()
{
	gRenderer->ClearScreen();
#if _MSC_VER == 1800
	gRenderer->SetColour(0x00, 0x00, 0x00, 0xFF);
#endif
	
	Mesh& mObject = func->GetObject();
	
	for (int index = 0; index < mObject.GetFaceCount(); index++)
	{
		
		Point A = mObject.GetPixel(mObject.GetIndice(index * 3 + 0));
		Point B = mObject.GetPixel(mObject.GetIndice(index * 3 + 1));
		Point C = mObject.GetPixel(mObject.GetIndice(index * 3 + 2));

		Triangle shape;

		shape.SetTriangle(A, B, C);

		shape.DrawEdges(*gRenderer, true,true,true); //A2B, B2C, C2A
		
		//for drawing surfaces of triangles
		//shape.DrawSurface(gRenderer);
	}

	//update screen
	gRenderer->UpdateScreen();
}



Grapher::~Grapher()
{
#if _MSC_VER == 1800
	SDL_Quit();
#endif
}