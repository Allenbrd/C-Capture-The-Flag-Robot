#ifndef VIEW_H
#define VIEW_H

#include "settings.h"  // Including the settings header
#include <stdbool.h>



void drawBackground();
void drawRobot(Robot robot);
void drawMarker(Marker marker);
void generateCoordinates(Robot *robot, Marker *marker);
void drawForeground(GameObjects *obj);
void initScene(GameObjects *obj);
void update(GameObjects *obj, Move lastMove);

#endif