3D grapher
==========

This is a software 3D grapher that I wrote for the fx9860G AU calculator.

This project was made with Visual Studio and the fx9860G SDK.

Not ready to release yet but I will make this available to the public so
I can show others my progress.


ToDo:
- insert checks into view.cpp for ViewBoundaries()

- instead of storing vertexes in mesh.h should instead store triangles

- rewrite det() function in the matrix class. using recursive functions suck



how to use:
-----------
Note: Take no responsibility for any harm this may cause to your calculator

1. Download fx9860G SDK. This can be found from the Casio website: http://edu.casio.com/

2. open up fx9860G SDK as admin

3. Project -> Open

4. Go to 3DGrapher/Calculator/fx98603DEngine

5. open 3DGraph.g1w with the fx9860G SDK

6. Project -> Build

7. This will generate a .G1A file, using CASIO FA-124 transfer the file to your calculator.

8. The program is executed from the calculator menu