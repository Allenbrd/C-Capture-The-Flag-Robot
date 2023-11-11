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

void printStack(MoveStack *stack) { // Helper function for debugging
    MoveNode *current = stack->top;
    while (current != NULL) {
        printf("%d -> ", current->move);
        current = current->next;
    }
    printf("NULL\n");
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
