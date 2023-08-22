
#ifndef GUI_H_
#define GUI_H_

#include "snake.h"

#define GRID_WIDTH 16
#define GRID_HEIGHT 16
#define GRID_STARTING_HEIGHT 80
#define GRID_STARTING_WIDTH 50
#define GRID_INC_DIST 20
#define TILE_SIDE_LEN 30

void draw_grid_base();
void update_grid(snakePiece* head, plot* fruit);

#endif
