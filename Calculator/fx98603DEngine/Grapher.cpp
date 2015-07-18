#include "Grapher.h"


Grapher::Grapher(Renderer* origRenderer, VWindow * origViewWindow) : GameStatus(origRenderer, GRAPHER)
{
	this->ViewWindow = origViewWindow;
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
	float xMin = this->ViewWindow->GetSettings().xMin;
	float xMax = this->ViewWindow->GetSettings().xMax;
	float xRange = xMax - xMin;

	float yMin = this->ViewWindow->GetSettings().yMin;
	float yMax = this->ViewWindow->GetSettings().yMax;
	float yRange = yMax - yMin;

	//work out which range is bigger
	float biggerRange = 1;
	if (xRange > yRange)
	{
		biggerRange = xRange;
	}
	else
	{
		biggerRange = yRange;
	}

	cam.Reset(biggerRange, biggerRange);


	float yaw = this->ViewWindow->GetSettings().yawAngle;
	float pitch = this->ViewWindow->GetSettings().pitchAngle;

	cam.RotateGlobal(pitch, 0, yaw);

	float xPos = this->ViewWindow->GetSettings().xCameraPos;
	float yPos = this->ViewWindow->GetSettings().yCameraPos;
	float zPos = this->ViewWindow->GetSettings().zCameraPos;

	cam.TranslationGlobal(xPos, yPos, zPos);

	return true;
}


bool Grapher::Input()
{
#if _MSC_VER != 1200
	while (SDL_PollEvent(&gRenderer->e) != 0)
	{
		if (gRenderer->e.type == SDL_QUIT)
		{
			this->nextState = QUIT;
			return false;
		}
		else if (gRenderer->e.type == SDL_KEYDOWN)
		{
			//first see if a UI event has occured
			UIOverlay.Input(&gRenderer->e, func);

			//if a UI event has occured then turn off input to grapher
			if (!UIOverlay.InputFromGrapherOverlay())
			{
				//no UI event has occured, all inputs are dirrected to the grapher
				switch (gRenderer->e.key.keysym.sym)
				{
				case SDLK_RIGHT:
					cam.RotateGlobal(0, 0, -5);
					break;

				case SDLK_LEFT:
					cam.RotateGlobal(0, 0, 5);
					break;

				case SDLK_UP:
				{
					float zAng = cam.GetRotHist()(2);
					zAng = zAng * (3.14159265 / 180.0);
					cam.RotateGlobal(5 * cos(zAng), 5 * sin(zAng), 0);
					break;
				}
				case SDLK_DOWN:
				{
					float zAng = cam.GetRotHist()(2);
					zAng = zAng * (3.14159265 / 180.0);
					cam.RotateGlobal(-5 * cos(zAng), -5 * sin(zAng), 0);
					break;
				}

				case SDLK_w:
				{
					cam.TranslationLocal(0, -0.5, 0);
					break;
				}
				case SDLK_s:
				{
					cam.TranslationLocal(0, 0.5, 0);
					break;
				}
				case SDLK_a:
				{
					cam.TranslationLocal(-0.5, 0, 0);
					break;
				}
				case SDLK_d:
				{
					cam.TranslationLocal(0.5, 0, 0);
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
	}
#endif
	
#if _MSC_VER == 1200
unsigned int key;
GetKey(&key);

	switch (key)
	{
	case KEY_CTRL_RIGHT:
		cam.RotateGlobal(0, 0, -5);
		break;
	case KEY_CTRL_LEFT:
		cam.RotateGlobal(0, 0, 5);
		break;

	case KEY_CTRL_UP:
	{
		float zAng = cam.GetRotHist()(2);
		zAng = zAng * (3.14159265 / 180.0);
		cam.RotateGlobal(5 * cos(zAng), 5 * sin(zAng), 0);
		break;
	}
	case KEY_CTRL_DOWN:
	{
		float zAng = cam.GetRotHist()(2);
		zAng = zAng * (3.14159265 / 180.0);
		cam.RotateGlobal(-5 * cos(zAng), -5 * sin(zAng), 0);
		break;
	}

	//up
	case KEY_CHAR_8:
	{
		cam.TranslationLocal(0, -0.5, 0);
		break;
	}

	//down
	case KEY_CHAR_2:
	{
		cam.TranslationLocal(0, 0.5, 0);
		break;
	}

	//left
	case KEY_CHAR_4:
	{
		cam.TranslationLocal(-0.5, 0, 0);
		break;
	}

	//right
	case KEY_CHAR_6:
	{
		cam.TranslationLocal(0.5, 0, 0);
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
	//see if UI is overriding grapher
	if (!UIOverlay.InputFromGrapherOverlay())
	{
		//grapher processing
		for (int j = 0; j < 6; j++)
		{
			//each function

			//if the function the do the projection
			if (func[j]->IsDrawable())
			{
				for (int i = 0; i < func[j]->GetObject().GetPixelstCount(); i++)
				{
					Vector Vertex = func[j]->GetObject().GetVertex(i);
					Vertex(0) *= ViewWindow->GetSettings().xScaling;
					Vertex(1) *= ViewWindow->GetSettings().yScaling;
					Vertex(2) *= ViewWindow->GetSettings().zScaling;
					func[j]->GetObject().GetPixel(i) = cam.Project3Dto2D(Vertex, gRenderer->SCREEN_WIDTH, gRenderer->SCREEN_HEIGHT);
				}
			}
		}
	}
	else
	{
		//UI override
		UIOverlay.Proccess();
	}
	
	return true;
}

void Grapher::Display()
{
	gRenderer->ClearScreen();
#if _MSC_VER != 1200
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
				Vector normalVec = shape.GetNormal();
				Point Centre = shape.GetCenterPoint();

				if (normalVec(2) <= 0) //facing camera
				{
					shape.DrawEdges(gRenderer, true, true, !(ViewWindow->GetSettings().useTriangleMesh), true); //A2B, B2C, C2A
				}
				else
				{
					//not facing camera
					if (ViewWindow->GetSettings().SolidMesh)
					{
						shape.DrawSurface(gRenderer);
						shape.DrawEdges(gRenderer, true, true, !(ViewWindow->GetSettings().useTriangleMesh), false); //A2B, B2C, C2A
					}
					else
					{
						shape.DrawEdges(gRenderer, true, true, !(ViewWindow->GetSettings().useTriangleMesh), true); //A2B, B2C, C2A
					}
				}
			}
		}
	}

	//render the UI overlay
	UIOverlay.Display(gRenderer);

	//update screen
	gRenderer->UpdateScreen();
}



Grapher::~Grapher()
{
#if _MSC_VER != 1200
	SDL_Quit();
#endif
}