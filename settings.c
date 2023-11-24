#include "settings.h"
#include <stdbool.h>

// Window dimensions 
const int winWidth = 750;
const int winHeight = 750;

// Grid dimensions
const int gridWidth = 10;
const int gridHeight = 10;

const bool showGrid = true;

// Padding around the grid
const int padding = 100;

// Wait time between each robot move
const int waitTime = 300;

// Marker and obstancle image sources
char largeMarkerImg[] = "assets/flag-60.png";
char smallMarkerImg[] = "assets/smallflag.png";
char obstacleImg[] = "assets/landmine.png";
char homeImg[] = "assets/home.png";

const int robotWidth = 55; // soldier's image width
const int obstacleWidth = 38; // obstacle's image width

const int nbrOfObstacles = 12; // maximum number of obstacles

const int numbeOfFrames = 10; // Number of frames in robot animation