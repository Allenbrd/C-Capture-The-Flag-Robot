#ifndef MODEL_H
#define MODEL_H

#include "settings.h"

typedef struct {
    int x;
    int y;
    int degrees;
    bool carriesMarker;
} Robot;

typedef enum {
    MOVE_FORWARD,
    TURN_RIGHT
} Move;

typedef struct MoveNode {
    Move move;
    struct MoveNode *next;
} MoveNode;

typedef struct {
    MoveNode *top;
} MoveStack;

void initGame(Robot *robot, char grid[gridWidth][gridHeight]);
bool canMoveForward(Robot *robot, char grid[gridWidth][gridHeight]);
void forward(Robot *robot, char grid[gridWidth][gridHeight]);
void right(Robot *robot, char grid[gridWidth][gridHeight]);
int atMarker(Robot *robot, char grid[gridWidth][gridHeight]);
void pickUpMarker(Robot *robot);

void pushMove(MoveStack *stack, Move move);
Move popMove(MoveStack *stack);
void reverseMove(Robot *robot, Move move, char grid[gridWidth][gridHeight]);


#endif