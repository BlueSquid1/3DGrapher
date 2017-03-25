3D grapher
==========

This is a 3D grapher which runs on the fx9860G Casio calculator and Microsoft Windows 7 or above. It works by evaluating equations entered by the user and then displaying them in a 3 dimensional space which can then be rotated and scaled to the user needs.

The fx9860G port was made with fx9860G SDK and is written in Embedded C++. The Windows port was made with Visual Studio 2013 and is written in C++. SDL is used on the Windows port for handling visuals.


Screenshots:
------------

![Graph on Calulator](https://github.com/BlueSquid1/3DGrapher/blob/master/Images/calculator_graph.PNG)

![Graph on PC](https://github.com/BlueSquid1/3DGrapher/blob/master/Images/PC_graph.PNG)


Build instructions for the fx9860G port:
----------------------------------------

1. Download fx9860G SDK. This can be found from the Casio website: http://edu.casio.com/

2. open fx9860G SDK as admin

3. Project -> Open

4. Go to /3DGrapher/Calculator/fx98603DEngine

5. open 3DGraph.g1w with the fx9860G SDK

6. Project -> Build

7. This will generate a .G1A file, using CASIO FA-124 transfer the file to your calculator.

8. The program can now be executed from the calculator menu


Build instructions for the Windows port:
----------------------------------------

1. Install Visual Studio 2013

2. Go to /3DGrapher/SDL/SDL3DEngine

3. Open the file SDL3DEngine.sln with Visual Studio 2013

4. Right click on the project and select build

5. You will now see the executable in the folder "/3DGrapher/SDL/SDL3DEngine/Debug/" however you will be missing the windows libraries to run it.

5. copy the folder "res" in "3DGrapher/SDL/SDL3DEngine/SDL3DEngine" to "/3DGrapher/SDL/SDL3DEngine/Debug/"

6. copy the .dll files from "/3DGrapher/lib/SDL2-2.0.5/lib/x86" and "/3DGrapher/lib/SDL2_ttf-2.0.14/lib/x86" to "/3DGrapher/SDL/SDL3DEngine/Debug/"

7. Run "SDL3DEngine.exe"