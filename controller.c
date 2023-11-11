int main(void) {
    // initializing game objects
    Robot robot = {0, 0, 0, false};
    Marker marker = {0, 0, false};

    GameObjects objects = {robot, marker};
    GameObjects tempObjects = objects; // Initialize temporary object to check if move is feasable
    MoveStack moveStack = {NULL}; // Initialize the stack to keep track of moves

    initScene(&objects); // initializing the scene's view

    bool markerFound = false;

    // Move to the bottom left corner of the grid
        bool atSouthBorder = false;
        while(atSouthBorder == false){
            if (atMarker(&objects)) {
                pickUpMarker(&objects);
                markerFound = true;
                break;
            }

            while(objects.robot.degrees != 180){ // Making the robot face south
                right(&objects);
                pushMove(&moveStack, TURN_RIGHT);
            }

            if(canGoForward(&objects) == true) {
                forward(&objects);
                pushMove(&moveStack, MOVE_FORWARD);
            }else{
                atSouthBorder = true;
            }
            
        }

        bool atWestBorder = false;
        while(atWestBorder == false){

            if (atMarker(&objects)) {
                pickUpMarker(&objects);
                markerFound = true;
                break;
            }
            
            while(objects.robot.degrees%360 != 270){
                right(&objects);
                pushMove(&moveStack, TURN_RIGHT);
            }

            if (canGoForward(&objects) == true) {
                forward(&objects);
                pushMove(&moveStack, MOVE_FORWARD);
            }else{
                atWestBorder = true;
            }

        }



    // Reset robot's direction to face east (right)
    while(objects.robot.degrees%360 != 90){
        right(&objects);
        pushMove(&moveStack, TURN_RIGHT);
    }

    // int direction = 1; // 1 for right, -1 for left

    // Main game loop
    while (!markerFound || moveStack.top != NULL) {
        if (!markerFound) {
            if (atMarker(&objects)) {
                pickUpMarker(&objects);
                markerFound = true;
            } else {

                bool atteinedWall = false;

                while(atteinedWall == false){
                    if (atMarker(&objects)) {
                        pickUpMarker(&objects);
                        markerFound = true;
                        break;
                    }
                   
                    if(canGoForward(&objects) == false){
                        atteinedWall = true;
                    }else{
                        forward(&objects);
                        pushMove(&moveStack, MOVE_FORWARD);
                    }

                }

                // Reset robot's direction to face north (updwards)
                while(objects.robot.degrees%360 != 0){
                    right(&objects);
                    pushMove(&moveStack, TURN_RIGHT);
                }
                forward(&objects);
                pushMove(&moveStack, MOVE_FORWARD);

                tempObjects = objects;
                right(&tempObjects);
                // forward(&tempObjects);

                // if(tempObjects.robot.x == objects.robot.x && tempObjects.robot.y == objects.robot.y){
                if(canGoForward(&tempObjects) == false){
                    right(&objects);
                    pushMove(&moveStack, TURN_RIGHT);

                    right(&objects);
                    pushMove(&moveStack, TURN_RIGHT);

                    right(&objects);
                    pushMove(&moveStack, TURN_RIGHT);
                }else{
                    right(&objects);
                    pushMove(&moveStack, TURN_RIGHT);
                }

                
            }

        } else {
            // Retrace steps back to spawn point
            Move lastMove = popMove(&moveStack);
            if (lastMove == MOVE_FORWARD) {
                // Reverse forward move
                reverseMove(&objects.robot, lastMove);
            } else if (lastMove == TURN_RIGHT) {
                // Reverse a right turn
                reverseMove(&objects.robot, lastMove);
            }
        }


        // Sleep or delay if necessary to visualize the movement
    }

    clearMoveStack(&moveStack); // Clean up any remaining moves

    // End of game, can add any finalization logic here if needed
    return 0;
}

