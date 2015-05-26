#include "Grapher.h"


Grapher::Grapher(Renderer* origRenderer) : GameStatus(origRenderer, GRAPHER)
{
}

bool Grapher::LoadFunctions(Function equation[6])
{
	for (int i = 0; i < 6; i++)
	{
		this->func[i] = &equation[i];
	}
	return true;
}

bool Grapher::Reset()
{
	return cam.Reset();
}


bool Grapher::Input()
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
			case SDLK_ESCAPE:
			{
				this->nextState = MAINMENU;
				return false;
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
	
	case KEY_CTRL_EXIT:
	{
		this->nextState = MAINMENU;
		return false;
	}
	
	default:
		break;
	}
#endif
	return true;
}

bool Grapher::Proccess()
{
	for (int j = 0; j < 6; j++)
	{
		//each function

		//if the function the do the projection
		if (func[j]->IsDrawable())
		{
			for (int i = 0; i < func[j]->GetObject().GetPixelstCount(); i++)
			{
				func[j]->GetObject().GetPixel(i) = cam.Project3Dto2D(func[j]->GetObject().GetVertex(i), gRenderer->SCREEN_WIDTH, gRenderer->SCREEN_HEIGHT);
			}
		}
	}
	
	return true;
}

void Grapher::Display()
{
	gRenderer->ClearScreen();
#if _MSC_VER == 1800
	gRenderer->SetColour(0x00, 0x00, 0x00, 0xFF);
#endif
	
	for (int i = 0; i < 6; i++)
	{
		//for each function

		if (func[i]->IsDrawable())
		{
			Mesh& mObject = func[i]->GetObject();

			for (int index = 0; index < mObject.GetFaceCount(); index++)
			{

				Point A = mObject.GetPixel(mObject.GetIndice(index * 3 + 0));
				Point B = mObject.GetPixel(mObject.GetIndice(index * 3 + 1));
				Point C = mObject.GetPixel(mObject.GetIndice(index * 3 + 2));

				Triangle shape;

				shape.SetTriangle(A, B, C);

				shape.DrawEdges(*gRenderer, true, true, true); //A2B, B2C, C2A

				//for drawing surfaces of triangles
				//shape.DrawSurface(gRenderer);
			}
		}
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