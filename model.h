typedef struct {
    int x;
    int y;
    int degrees;
    bool carriesMarker;
} Robot;

typedef struct {
    int x;
    int y;
    bool pickedUp;
} Marker;

typedef struct {
    Robot robot;
    Marker marker;
} GameObjects;

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