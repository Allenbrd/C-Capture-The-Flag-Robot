#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "model.h"
#include "settings.h"

void search(Robot *robot, char grid[gridWidth][gridHeight], MoveStack *moveStack){
    int random;
    while(robot->carriesMarker == false){
        
        if(atMarker(robot, grid)){
            pickUpMarker(robot);
        }

        random = rand() % 10;
        switch(random){
            case 0 ... 7:
                if(canMoveForward(robot, grid)){
                    forward(robot, grid);
                    pushMove(moveStack, MOVE_FORWARD);
                }
                break;
            case 8:
                right(robot, grid);
                pushMove(moveStack, TURN_RIGHT);
                break;
            case 9:
                for(int i = 0; i < 3; i++){
                    right(robot, grid);
                    pushMove(moveStack, TURN_RIGHT);
                }
                break;
        }
    }
}

void getBackHome(Robot *robot, char grid[gridWidth][gridHeight], MoveStack *moveStack) {
    while (moveStack->top != NULL) {
        Move lastMove = popMove(moveStack);
            if (lastMove == MOVE_FORWARD) {
                // Reverse forward move
                reverseMove(robot, lastMove, grid);
            } else if (lastMove == TURN_RIGHT) {
                // Reverse a right turn
                reverseMove(robot, lastMove, grid);
            }
    }
}

void main(void) {

    Robot robot;
    robot.carriesMarker = false;
    char grid[gridWidth][gridHeight];
    MoveStack moveStack = {NULL};

    initGame(&robot, grid);

    search(&robot, grid, &moveStack);

    getBackHome(&robot, grid, &moveStack);

    printf("Game Over: our soldier brought the flag home!");
        
}