# MATRIX-BACKTRACKING-VISUALIZER
A project made for educational purposes, generates visually paths followed by a backtracking-related pathfind algorythm



~~~~~~~~~~ Backtracking Viewer ~~~~~~~~~~~~~~~



Usage command: ./WorldWideC++.exe Pathfind 0 0 5 5

(What this means?)

Basically, we tell the program that we have to start from (0, 0) and get to (5, 5). The "Pathfind" argument ensures that we use the current mode, respectively the visualization of the backtracking in the plan.

!! OUR MATRIX MUST BE LOADED IN MATRIXTEST.json !!
Initially, the program reads from there the number of rows and the number of columns, then the matrix must be entered, WITH -1 REPRESENTING THE WALLS, AND 0 THE NORMAL ROAD, WHICH THE ALGORITHM CAN TAKE INTO ACCOUNT



At runtime, the program will display a window. Wait until the first road appears, which is marked with numbers and the color RED.

Then click on the window to display the next possibility.

The window will close at the end of the possibilities.


~~~~~~~ C: MatthewAlgo 2021 ~~~~~~~~~~~
