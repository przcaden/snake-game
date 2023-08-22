
#include "gui.h"
#include <stdint.h>
#include <raylib.h>
#include <string.h>

// Clear contents of the grid on the GUI.
void draw_grid_base()
{
    for (int i=0; i<GRID_WIDTH; i++)
    {
        for (int j=0; j<GRID_HEIGHT; j++)
        {
            uint16_t tile_x = GRID_STARTING_WIDTH + (i-1 * GRID_INC_DIST) + (i * TILE_SIDE_LEN);
            uint16_t tile_y = GRID_STARTING_HEIGHT + (j-1 * GRID_INC_DIST) + (j * TILE_SIDE_LEN);
            DrawRectangle(tile_x, tile_y, TILE_SIDE_LEN, TILE_SIDE_LEN, GRAY);
        }
    }
}

// Update grid visuals in the GUI.
void update_grid(snakePiece* head, plot* fruit)
{
    // Update fruit tile
    uint16_t tile_x = GRID_STARTING_WIDTH + (fruit->x-1 * GRID_INC_DIST) + (fruit->x * TILE_SIDE_LEN);
    uint16_t tile_y = GRID_STARTING_HEIGHT + (fruit->y-1 * GRID_INC_DIST) + (fruit->y * TILE_SIDE_LEN);
    DrawRectangle(tile_x, tile_y, TILE_SIDE_LEN, TILE_SIDE_LEN, RED);

    // Update head tile
    snakePiece* temp = head;
    tile_x = GRID_STARTING_WIDTH + (temp->loc->x-1 * GRID_INC_DIST) + (temp->loc->x * TILE_SIDE_LEN);
    tile_y = GRID_STARTING_HEIGHT + (temp->loc->y-1 * GRID_INC_DIST) + (temp->loc->y * TILE_SIDE_LEN);
    DrawRectangle(tile_x, tile_y, TILE_SIDE_LEN, TILE_SIDE_LEN, DARKGREEN);
    temp = temp->next;

    // Update tiles of body
    while (temp != NULL)
    {
        tile_x = GRID_STARTING_WIDTH + (temp->loc->x-1 * GRID_INC_DIST) + (temp->loc->x * TILE_SIDE_LEN);
        tile_y = GRID_STARTING_HEIGHT + (temp->loc->y-1 * GRID_INC_DIST) + (temp->loc->y * TILE_SIDE_LEN);
        DrawRectangle(tile_x, tile_y, TILE_SIDE_LEN, TILE_SIDE_LEN, GREEN);
        temp = temp->next;
    }
}