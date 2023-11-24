#ifndef VIEW_H
#define VIEW_H

#include "model.h"

void drawForeground(Robot *robot, char grid[gridWidth][gridHeight]);
void initView(Robot *robot, char grid[gridWidth][gridHeight]);
void update(Robot *robot, char grid[gridWidth][gridHeight], Move lastMove);

#endif