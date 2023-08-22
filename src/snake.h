
#ifndef SNAKE_H_
#define SNAKE_H_

#include <stdbool.h>
#include <stdint.h>
#include "key_handler.h"

// Set of coordinates for objects on the grid.
typedef struct plot
{
    uint8_t x;
    uint8_t y;
} plot;

// Node structure for the snake.
// The "next" piece refers to the next closest to the tail.
typedef struct snakePiece
{
    plot* loc;
    struct snakePiece* next;
    struct snakePiece* prev;
    enum direction moving_dir;
} snakePiece;

// Contains info for the current playing session.
typedef struct sessionInfo
{
    snakePiece* head;
    snakePiece* tail;
    plot* fruit_loc;
    uint64_t score;
    bool game_started;
} sessionInfo;

bool snake_contains(snakePiece* head, plot* pos);
plot* getRandomPos(snakePiece* head);
void update_snake(sessionInfo* session, enum direction key_pressed);
void update_head(sessionInfo* session, enum direction key_pressed);

#endif
