#include <stdbool.h>
#include <stdlib.h>
#include "view.h"
#include "settings.h"

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
        return -1; // Or some other invalid move value
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

void reverseMove(Robot *robot, Move move) {
    if (move == MOVE_FORWARD) {
        // Move backward
        switch (robot->degrees % 360) {
            case 0:
                robot->y++;
                break;
            case 90:
                robot->x--;
                break;
            case 180:
                robot->y--;
                break;
            case 270:
                robot->x++;
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


void forward(GameObjects *obj){
    // move the robot to the next square depending on the direction it is facing
    switch(obj->robot.degrees%360){
        case 0: // if facing north, move one square upwards
            if (obj->robot.y > 0) {
                obj->robot.y--;
            }
            break;
        case 90: // if facing east, move one square right
            if (obj->robot.x < gridWidth - 1) {
                obj->robot.x++;
            }
            break;
        case 180: // if facing south, move one square downwards
            if (obj->robot.y < gridHeight - 1) {
                obj->robot.y++;
            }
            break;
        case 270: // if facing west, move one square left
            if (obj->robot.x > 0) {
                obj->robot.x--;
            }
            break;
    }

    update(obj, MOVE_FORWARD); // Update the view with the new position
}

bool canGoForward(GameObjects *obj){

    GameObjects tempObj = *obj;

    // move the robot to the next square depending on the direction it is facing
    switch(tempObj.robot.degrees%360){
        case 0: // if facing north, move one square upwards
            if (tempObj.robot.y > 0) {
                tempObj.robot.y--;
            }
            break;
        case 90: // if facing east, move one square right
            if (tempObj.robot.x < gridWidth - 1) {
                tempObj.robot.x++;
            }
            break;
        case 180: // if facing south, move one square downwards
            if (tempObj.robot.y < gridHeight - 1) {
                tempObj.robot.y++;
            }
            break;
        case 270: // if facing west, move one square left
            if (tempObj.robot.x > 0) {
                tempObj.robot.x--;
            }
            break;
    }

    if (tempObj.robot.y != obj->robot.y || tempObj.robot.x != obj->robot.x) {
        return true;
    }else{
        return false;
    }
}

int atMarker(Robot *robot, char grid[gridWidth][gridHeight]) {
    return grid[robot->y][robot->x] == "marker";
}

void pickUpMarker(GameObjects *obj) {
    obj->marker.pickedUp = true;
    obj->robot.carriesMarker = true;
}

void right(GameObjects *obj){
    obj->robot.degrees += 90; // rotating 90 degrees clockwise
    update(obj, TURN_RIGHT); // Update the view with the new position
}

