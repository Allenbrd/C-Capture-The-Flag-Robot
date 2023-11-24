#include <stdbool.h>
#include <stdlib.h>
#include "view.h"
#include "settings.h"
#include <time.h>

#include <stdio.h>

// Functions to work with MoveStack
void pushMove(MoveStack *stack, Move move);
Move popMove(MoveStack *stack);
void clearMoveStack(MoveStack *stack);

void pushMove(MoveStack *stack, Move move) {
    MoveNode *newNode = (MoveNode *)malloc(sizeof(MoveNode));
    newNode->move = move;
    newNode->next = stack->top;
    stack->top = newNode;
}

Move popMove(MoveStack *stack) {
    if (stack->top == NULL) {
        return -1;
    }
    MoveNode *topNode = stack->top;
    Move move = topNode->move;
    stack->top = topNode->next;
    free(topNode);
    return move;
}

void clearMoveStack(MoveStack *stack) {
    while (stack->top != NULL) {
        popMove(stack);
    }
}

void reverseMove(Robot *robot, Move move, char grid[gridWidth][gridHeight]) {
    if (move == MOVE_FORWARD) {
        // Move backward
        switch (robot->degrees % 360) {
            case 0:
                robot->y++;
                update(robot, grid, move);
                break;
            case 90:
                robot->x--;
                update(robot, grid, move);
                break;
            case 180:
                robot->y--;
                update(robot, grid, move);
                break;
            case 270:
                robot->x++;
                update(robot, grid, move);
                break;
        }
    } else if (move == TURN_RIGHT) {
        // To reverse a right turn, we turn left (which is 3 right turns)
        robot->degrees -= 90;
        if (robot->degrees < 0) {
            robot->degrees += 360; // Ensure degrees stays within 0-359
        }
    }
}


bool canMoveForward(Robot *robot, char grid[gridWidth][gridHeight]){
    // Check the next square based on the robot's current direction
    switch(robot->degrees%360){
        case 0:
            return robot->y > 0 && grid[robot->x][robot->y - 1] != 'o';
        case 90:
            return robot->x < gridWidth - 1 && grid[robot->x + 1][robot->y] != 'o';
        case 180:
            return robot->y < gridHeight - 1 && grid[robot->x][robot->y + 1] != 'o';
        case 270:
            return robot->x > 0 && grid[robot->x - 1][robot->y] != 'o';
        default:
            return 0;
    }
 }

void forward(Robot *robot, char grid[gridWidth][gridHeight]){
    // move the robot to the next square depending on the direction it is facing
    switch(robot->degrees%360){
        case 0: // if facing north, move one square upwards
            robot->y--;
            break;
        case 90: // if facing east, move one square right
            robot->x++;
            break;
        case 180: // if facing south, move one square downwards
            robot->y++;
            break;
        case 270: // if facing west, move one square left
            robot->x--;
            break;
    }

    update(robot, grid, MOVE_FORWARD); // Update the view with the new position
}

void right(Robot *robot, char grid[gridWidth][gridHeight]){
    robot->degrees += 90; // rotating 90 degrees clockwise
    update(robot, grid, TURN_RIGHT); // Update the view with the new position
}

int atMarker(Robot *robot, char grid[gridWidth][gridHeight]) {
    return grid[robot->x][robot->y] == 'm';
}

void pickUpMarker(Robot *robot) {
    robot->carriesMarker = true;
}


// Generates random coordinates for game objects
void generateCoordinates(Robot *robot, char grid[gridWidth][gridHeight]) {
    srand((unsigned int)time(NULL)); // initializing the rand function

    int markerX, markerY;
    bool overlaping;
    
    do{
        overlaping = false;

        // Generating the robot's coordinates and starting angle
        robot->x = rand() % gridWidth;
        robot->y = rand() % gridHeight;
        robot->degrees = (rand() % 4) * 90;

        // Generating the marker's coordinates
        markerX = rand() % gridWidth;
        markerY = rand() % gridHeight;

        // Generating the obstacles' coordinates 

        int obstacles[nbrOfObstacles][2];

        for(int i = 0; i <= nbrOfObstacles; i++){
            int obstacleX = rand()%gridWidth;
            int obstacleY = rand()%gridHeight;
            if((obstacleX == robot->x && obstacleY == robot->y) || (obstacleX == markerX && obstacleY == markerY)){
                overlaping = true;
            }else{
                obstacles[i][0] = obstacleX;
                obstacles[i][1] = obstacleY;
            }
        }

        if(overlaping != true){
            grid[markerX][markerY] = 'm';
            for(int i = 0; i <= nbrOfObstacles; i++){
                grid[obstacles[i][0]][obstacles[i][1]] = 'o';
            }
        }


    }while(overlaping);
}

void initGame(Robot *robot, char grid[gridWidth][gridHeight]){
    generateCoordinates(robot, grid);
    initView(robot, grid);
}