#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "graphics/graphics.h"

#include "view.h"
#include "settings.h"


// Initializing variable to store the squares' width
int squareWidth;
int *pointToSW = &squareWidth;


// Draws the game's grid
void drawGrid(void){
    setColour(black);

    // Drawing horizontal lines
    for(int i = 0; i <= gridHeight; i++){
        drawLine(
            padding,
            padding+(i*squareWidth),
            winWidth-padding,
            padding+(i*squareWidth)
        );
    }

    // Drawing vertical lines
    for(int i = 0; i <= gridWidth; i++){
        drawLine(
            padding+(i*squareWidth),
            padding,
            padding+(i*squareWidth),
            winHeight-padding
        );
    }
}

void drawSmallMarker(Robot *robot, double x, double y){
    if(robot->carriesMarker == true){
        double imgX = x+squareWidth/2.5;
        double imgY = y-squareWidth/3.5;

        displayImage(smallMarkerImg, (int)imgX, (int)imgY); // renders the small marker's image if robot is carrying it
    }
}

void drawRobot(Robot *robot){

    // Computing the needed padding to center robot on square
    int imgPadding = (squareWidth - robotWidth) / 2; 

    // Computing the robot's rotation angle for direction
    int direction = robot->degrees%360;

    // converting square postions to actual coordinates
    double x = padding + (robot->x) * squareWidth + imgPadding;
    double y = padding + (robot->y) * squareWidth + imgPadding;

    char imgSource[] = "frame_00_delay-0.1s.png";

    drawSmallMarker(robot, x, y);

    // defining drawing positions according to provided angle
    switch(direction){

        case 0: // if 0 degrees, face north
            { 
                char path[] = "assets/soldier/right/";
                strcat(path, imgSource);
                displayImage(path, (int)x, (int)y);
                break;
            }

        case 90: // if 90 degrees, face east
            {
                char path[] = "assets/soldier/right/";
                strcat(path, imgSource);
                displayImage(path, (int)x, (int)y);
                break;
            }

        case 180: // if 180 degrees, face south
            {
                char path[] = "assets/soldier/left/";
                strcat(path, imgSource);
                displayImage(path, (int)x, (int)y);
                break;
            }

        case 270: // if 180 degrees, face south
            {
                char path[] = "assets/soldier/left/";
                strcat(path, imgSource);
                displayImage(path, (int)x, (int)y);
                break;
            }
    }

    

}

// Draws the marker
void drawMarker(char grid[gridWidth][gridHeight]){
    // Looping trough the grid to identify the marker's position
    for (int i = 0; i < gridWidth; ++i) {
        for (int j = 0; j < gridHeight; ++j) {
            if (grid[i][j] == 'm') {
                // Computing the marker's coordinates
                double xCoordinates = padding + i * squareWidth;
                double yCoordinates = padding + j * squareWidth;

                displayImage(largeMarkerImg, xCoordinates, yCoordinates); // Rendering the marker's image
            }
        }
    }
}

// Draws obstacles
void drawObstacles(char grid[gridWidth][gridHeight]){
    // Looping trough the grid to identify the marker's position
    for (int i = 0; i < gridWidth; ++i) {
        for (int j = 0; j < gridHeight; ++j) {
            if (grid[i][j] == 'o') {
                // Computing the marker's coordinates
                double xCoordinates = padding + ((squareWidth-obstacleWidth)/2) + i * squareWidth;
                double yCoordinates = padding + ((squareWidth-obstacleWidth)/2) + j * squareWidth;

                displayImage(obstacleImg, xCoordinates, yCoordinates); // Rendering the marker's image
            }
        }
    }
}

// Draws foreground
void drawForeground(Robot *robot, char grid[gridWidth][gridHeight]){

    foreground();

    drawMarker(grid);
    drawRobot(robot);
}

void drawBackground(Robot *robot, char grid[gridWidth][gridHeight]){

    // Computing a single square's width
    *pointToSW = (winWidth-(2*padding))/gridWidth;

    setWindowSize(winWidth, winHeight);

    background();

    char bgPath[] = "assets/background.png";

    displayImage(bgPath, 0, 0);

    displayImage(homeImg, padding + (robot->x * squareWidth), padding + (robot->y * squareWidth));

    if(showGrid){
        drawGrid();
    }

    drawObstacles(grid);

}

// Initializing the game's scene and interface
void initView(Robot *robot, char grid[gridWidth][gridHeight]){

    drawBackground(robot, grid);
    drawForeground(robot, grid); // passing the pointer to drawForeground

}


// Draws tobot animation when moving to new square
void animateRobot(Robot *robot, char grid[gridWidth][gridHeight], Move lastMove){
    // Computing the time and distance to be 
    int timePerFrame = waitTime/numbeOfFrames;
    int distancePerFrame = squareWidth/numbeOfFrames;

    int imgPadding = (squareWidth - robotWidth) / 2; 

    char frames[10][24] = {
        "frame_00_delay-0.1s.png",
        "frame_01_delay-0.1s.png",
        "frame_02_delay-0.1s.png",
        "frame_03_delay-0.1s.png",
        "frame_04_delay-0.1s.png",
        "frame_05_delay-0.1s.png",
        "frame_06_delay-0.1s.png",
        "frame_07_delay-0.1s.png",
        "frame_08_delay-0.1s.png",
        "frame_09_delay-0.1s.png",
    };

    if(lastMove == MOVE_FORWARD){

        char iteration;

        // for each frame (in ten frames), drawing new robot position
        for(int i = 0; i < numbeOfFrames; i++){

            foreground();
            clear(); // clearing foreground view
            if(robot->carriesMarker == false){
                drawMarker(grid); // drawing the marker if it has not been picked up yet
            }

            sprintf(&iteration, "%d", i);

            double x, y;
            char path[100];

            switch(robot->degrees % 360){
                case 0: // if 0 degrees, face north
                    {
                    if(robot->carriesMarker == true){ // if the robot carries a marker, draw it opposite to its direction
                        x = padding + (robot->x) * squareWidth + imgPadding;
                        y = (padding + (robot->y - 1) * squareWidth) + imgPadding*(1+i/10) + i * distancePerFrame;
                    }else{ // else, draw it going its direction's way
                        x = padding + (robot->x) * squareWidth + imgPadding;
                        y = (padding + (robot->y + 1) * squareWidth) + imgPadding*(1+i/10) - i * distancePerFrame;
                    }
                    strcpy(path, "assets/soldier/right/");
                    if(i==0){
                        strcat(path, "frame_00_delay-0.1s.png");
                    }else{
                    strcat(path, frames[i]);
                    }
                    break;
                    }
                case 90: // if 90 degrees, face east
                    {
                    if(robot->carriesMarker == true){
                        x = (padding + (robot->x + 1) * squareWidth) + imgPadding*(1+i/10) - i * distancePerFrame;
                        y = padding + (robot->y) * squareWidth + imgPadding;
                        strcpy(path, "assets/soldier/left/");
                    }else{
                        x = (padding + (robot->x - 1) * squareWidth) + imgPadding*(1+i/10) + i * distancePerFrame;
                        y = padding + (robot->y) * squareWidth + imgPadding;
                        strcpy(path, "assets/soldier/right/");
                    }
                    if(i==0){
                        strcat(path, "frame_00_delay-0.1s.png");
                    }else{
                    strcat(path, frames[i]);
                    }
                    break;
                    }
                case 180: // if 180 degrees, face south
                    { 
                    if(robot->carriesMarker == true){
                        x = padding + (robot->x) * squareWidth + imgPadding;
                        y = (padding + (robot->y + 1) * squareWidth) + imgPadding*(1+i/10) - i * distancePerFrame;
                        strcpy(path, "assets/soldier/right/");
                    }else{
                        x = padding + (robot->x) * squareWidth + imgPadding;
                        y = (padding + (robot->y - 1) * squareWidth) + imgPadding*(1+i/10) + i * distancePerFrame;
                        strcpy(path, "assets/soldier/left/");
                    }
                    if(i==0){
                        strcat(path, "frame_00_delay-0.1s.png");
                    }else{
                    strcat(path, frames[i]);
                    }
                    break;
                    }
                case 270: // if 270 degrees, face west
                    {
                    if(robot->carriesMarker == true){ // if the robot carries a marker, draw it opposite to its direction
                        x = (padding + (robot->x - 1) * squareWidth) + imgPadding*(1+i/10) + i * distancePerFrame;
                        y = padding + (robot->y) * squareWidth + imgPadding;
                        strcpy(path, "assets/soldier/right/");
                    }else{ 
                        x = (padding + (robot->x + 1) * squareWidth) + imgPadding*(1+i/10) - i * distancePerFrame;
                        y = padding + (robot->y) * squareWidth + imgPadding;
                        strcpy(path, "assets/soldier/left/");
                    }
                    if(i==0){
                        strcat(path, "frame_00_delay-0.1s.png");
                    }else{
                    strcat(path, frames[i]);
                    }
                    break;
                    }
            }

            displayImage(path, (int)x, (int)y);

            drawSmallMarker(robot, x, y);

            sleep(timePerFrame);
        }

    }else{

        // If the robot, is not moving forward, simply draw it idle
        drawRobot(robot);

        sleep(timePerFrame);
    }
}

// Update the game's interface to display changes and new positions
void update(Robot *robot, char grid[gridWidth][gridHeight], Move lastMove)
{
    foreground();
    clear(); // clearing foreground view
    if(robot->carriesMarker == false){
        drawMarker(grid); // drawing the marker if it has not been picked up yet
    }

    animateRobot(robot, grid, lastMove);
    
}
