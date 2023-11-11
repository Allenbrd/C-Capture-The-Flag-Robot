// importing graphics library
#include "graphics/graphics.h"

// importing local view and settings
#include "view.h"
#include "settings.h"

// importing c libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

int squareWidth;
int *pointToSW = &squareWidth;

void drawBackground(){

    // Computing a single square's width
    *pointToSW = (winWidth-(2*padding))/gridWidth;

    setWindowSize(winWidth, winHeight);
    background();

    char bgpath[] = "resources/background.png";

    displayImage(bgpath, 0, 0);
    
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

void drawRobot(Robot robot){

    int imgPadding = (squareWidth - imageWidth) / 2; 

    // computing the robot's degree of rotation
    int direction = robot.degrees%360;

    // converting square postions to actual coordinates
    double x = padding + (robot.x) * squareWidth + imgPadding;
    double y = padding + (robot.y) * squareWidth + imgPadding;

    char imgSource[] = "frame_00_delay-0.1s.png";

    // defining drawing positions according to provided angle
    switch(direction){

        case 0: // if 0 degrees, face north
            { 
                char path[] = "resources/soldier/right/";
                strcat(path, imgSource);
                displayImage(path, (int)x, (int)y); // renders the small marker's image if robot is carrying it
                break;
            }

        case 90: // if 90 degrees, face east
            {
                char path[] = "resources/soldier/right/";
                strcat(path, imgSource);
                displayImage(path, (int)x, (int)y); // renders the small marker's image if robot is carrying it
                break;
            }

        case 180: // if 180 degrees, face south
            {
                char path[] = "resources/soldier/left/";
                strcat(path, imgSource);
                displayImage(path, (int)x, (int)y); // renders the small marker's image if robot is carrying it
                break;
            }

        case 270: // if 180 degrees, face south
            {
                char path[] = "resources/soldier/left/";
                strcat(path, imgSource);
                displayImage(path, (int)x, (int)y); // renders the small marker's image if robot is carrying it
                break;
            }
    }

    // if(robot.carriesMarker == true){
    //     double imgX = x;
    //     double imgY = y;

    //     displayImage(smallMarkerImg, (int)x, (int)y); // renders the small marker's image if robot is carrying it
    // }

}

// Draws the marker
void drawMarker(Marker marker){

    // Computing the marker's actual coordinates
    double xCoordinates = padding + marker.x * squareWidth;
    double yCoordinates = padding + marker.y * squareWidth;

    displayImage(largeMarkerImg, xCoordinates, yCoordinates); // Rendering the marker's image
}

static int coordinates[4]; // Use static storage duration for the array


// Generates random coordinates for game objects
void generateCoordinates(Robot *robot, Marker *marker) {
    srand((unsigned int)time(NULL)); // initializing the rand function

    // Ensure that robot and marker don't overlap
    do {
        marker->x = rand() % gridWidth;
        marker->y = rand() % gridHeight;
        
        robot->x = rand() % gridWidth;
        robot->y = rand() % gridHeight;

        robot->degrees = (rand() % 4) * 90;

    } while (robot->x == marker->x && robot->y == marker->y);
}


// Drawing game objects
void drawForeground(GameObjects *obj){
    foreground();

    if(obj->marker.pickedUp == false){
        drawMarker(obj->marker); // drawing the marker if it has not been picked up yet
    }

    drawRobot(obj->robot); // drawing the robot
}

// Initializing the game's scene and interface
void initScene(GameObjects *obj){

    drawBackground();
    generateCoordinates(&obj->robot, &obj->marker); // passing pointers to the elements
    drawForeground(obj); // passing the pointer to drawForeground

}

// Update the game's interface to display changes and new positions
void update(GameObjects *obj, Move lastMove)
{
    foreground();
    clear(); // clearing foreground view
    if(obj->marker.pickedUp == false){
        drawMarker(obj->marker); // drawing the marker if it has not been picked up yet
    }

    int timePerFrame = waitTime/numbeOfFrames;
    int distancePerFrame = squareWidth/numbeOfFrames;

    int imgPadding = (squareWidth - imageWidth) / 2; 

    // double x, y;

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


    char iteration;


    if(lastMove == MOVE_FORWARD){

        for(int i = 0; i < 10; i++){

            foreground();
            clear(); // clearing foreground view
            if(obj->marker.pickedUp == false){
                drawMarker(obj->marker); // drawing the marker if it has not been picked up yet
            }

            sprintf(&iteration, "%d", i);
            double x, y;
            int direction = obj->robot.degrees % 360; 
            char path[100];

            switch(direction){
                case 0: // if 0 degrees, face north
                    {
                    x = padding + (obj->robot.x) * squareWidth + imgPadding;
                    y = (padding + (obj->robot.y + 1) * squareWidth) + imgPadding*(1+i/10) - i * distancePerFrame;
                    strcpy(path, "resources/soldier/right/");
                    strcat(path, frames[i]);
                    displayImage(path, (int)x, (int)y);
                    break;
                    }
                case 90: // if 90 degrees, face east
                    {
                    x = (padding + (obj->robot.x - 1) * squareWidth) + imgPadding*(1+i/10) + i * distancePerFrame;
                    y = padding + (obj->robot.y) * squareWidth + imgPadding;
                    strcpy(path, "resources/soldier/right/");
                    strcat(path, frames[i]);
                    displayImage(path, (int)x, (int)y);
                    break;
                    }
                case 180: // if 180 degrees, face south
                    { 
                    x = padding + (obj->robot.x) * squareWidth + imgPadding;
                    y = (padding + (obj->robot.y - 1) * squareWidth) + imgPadding*(1+i/10) + i * distancePerFrame;
                    strcpy(path, "resources/soldier/left/");
                    strcat(path, frames[i]);
                    displayImage(path, (int)x, (int)y);
                    break;
                    }
                case 270: // if 270 degrees, face west
                    {
                    x = (padding + (obj->robot.x + 1) * squareWidth) + imgPadding*(1+i/10) - i * distancePerFrame;
                    y = padding + (obj->robot.y) * squareWidth + imgPadding;
                    strcpy(path, "resources/soldier/left/");
                    strcat(path, frames[i]);
                    displayImage(path, (int)x, (int)y);
                    break;
                    }
            }

            sleep(timePerFrame);
        }

    }else{

        drawRobot(obj->robot);

        sleep(timePerFrame);
    }

}
