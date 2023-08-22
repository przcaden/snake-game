
#include "snake.h"
#include "gui.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Look through all snake pieces to see if they contain the given coords.
bool snake_contains(snakePiece* head, plot* pos)
{
    snakePiece* temp = head;
    while (temp != NULL)
    {
        if (temp->loc->x == pos->x && temp->loc->y == pos->y) return true;
        temp = temp->next;
    }
    return false;
}

// Generate a random plot within the grid.
plot* getRandomPos(snakePiece* head)
{
    bool verified = 0;
    plot* rand_pos = malloc(sizeof(plot));

    while (!verified)
    {
        rand_pos->x = rand() % GRID_WIDTH;
        rand_pos->y = rand() % GRID_HEIGHT;
        if (!snake_contains(head, rand_pos)) verified = 1;
    }
    return rand_pos;
}

void update_head(sessionInfo* session, enum direction key_pressed)
{
    // Update head position based on arrow key pressed
    switch (key_pressed)
    {
        case key_down:
            session->head->loc->y++;
            break;
        case key_up:
            session->head->loc->y--;
            break;
        case key_left:
            session->head->loc->x--;
            break;
        case key_right:
            session->head->loc->x++;
            break;
    }
}

// Update position of snake based on moving direction
void update_snake(sessionInfo* session, enum direction key_pressed)
{
    update_head(session, key_pressed);

    if (session->tail == NULL) return;

    // Update body positions; pieces will follow the direction of the previous
    snakePiece* temp = session->tail;
    while (temp->prev != NULL)
    {
        switch (temp->moving_dir)
        {
            case key_down:
                temp->loc->y++;
                break;
            case key_up:
                temp->loc->y--;
                break;
            case key_left:
                temp->loc->x--;
                break;
            case key_right:
                temp->loc->x++;
                break;
        }
        if (temp->prev != NULL)
            temp->moving_dir = temp->prev->moving_dir;
        temp = temp->prev;
    }
}