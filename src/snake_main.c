
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <raylib.h>
#include "key_handler.h"
#include "snake.h"
#include "gui.h"


void game_logic(sessionInfo* session, bool* input_lock);
void pre_game_loop(sessionInfo* session, char* highScore, int* UPDATES_PER_SEC);
void game_session_loop(sessionInfo* session, char* highScore, int* UPDATES_PER_SEC);
void game_over_loop(sessionInfo* session, char* highScore);

/* //////////////////////////
//       GLOBAL DATA       //
////////////////////////// */

const uint16_t WINDOW_WIDTH = 920;
const uint16_t WINDOW_HEIGHT = 660;


/* //////////////////////////////
//      EVENT/DATA HANDLING    //
////////////////////////////// */

void game_logic(sessionInfo* session, bool* input_lock)
{   
    snakePiece* head = session->head;
    plot* fruit = session->fruit_loc;

    // debug
    printf("Head location: (%d, %d) ", head->loc->x, head->loc->y);
    if (head->next != NULL) printf("Body location: (%d, %d) ", head->next->loc->x, head->next->loc->y);
    printf("Fruit location: (%d, %d)\n", fruit->x, fruit->y);

    // Handle directional input
    if (!(*input_lock)) arrowKeyHandler(&(session->head->moving_dir));
    *input_lock = !(*input_lock);

    // Check if head has collided with body; game over if so
    if (snake_contains(session->head->next, session->head->loc)) session->game_started = 0;

    // Check if head has collided with walls, game over if so
    if (session->head->loc->x >= GRID_WIDTH || session->head->loc->x < 0 ||
        session->head->loc->y >= GRID_HEIGHT || session->head->loc->y < 0)
    {
        session->game_started = 0;
        return;
    }

    // Check if head has collided with fruit and update snake position
    if (head->loc->x == fruit->x && head->loc->y == fruit->y)
    {
        session->fruit_loc = getRandomPos(head);
        session->score++;

        // Generate new head piece
        snakePiece* body = session->head;
        if (session->score == 1) session->tail = body;
        snakePiece* new_head = malloc(sizeof(snakePiece));
        plot* new_plot = malloc(sizeof(plot));
        *new_plot = (plot) { head->loc->x, head->loc->y };
        *new_head = (snakePiece) { new_plot, body, NULL, head->moving_dir };
        // memcpy(new_head, head, sizeof(snakePiece));

        // Orient pointers for new piece
        session->head = new_head;
        body->prev = new_head;
        update_head(session, session->head->moving_dir);
    }
    else update_snake(session, session->head->moving_dir);
}

// First loop ran before the game is started by the player.
void pre_game_loop(sessionInfo* session, char* highScore, int* UPDATES_PER_SEC)
{
    enum difficulty dif = easy;
    while (!session->game_started)
    {
        if (IsKeyPressed(KEY_ESCAPE) || WindowShouldClose()) CloseWindow();
        
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Press ENTER to Begin", 190, 20, 18, BLACK);
            
            // Draw high score, centered on score length
            DrawText("High Score:", 664, 90, 24, BLACK);
            DrawText(highScore, 730-(6*strlen(highScore)), 130, 24, BLACK);

            // Draw player's difficulty selection
            DrawText("Pick a Difficulty", 635, 200, 24, BLACK);
            DrawText("Use arrow keys to select:", 580, 235, 24, BLACK);
            DrawText("Easy    Medium    Hard", 593, 290, 24, BLACK);

            // Display box around difficulty selection
            switch(dif)
            {
                case easy:
                    // DrawRectangleLines(int posX, int posY, int width, int height, RED);
                    DrawRectangleLines(585, 285, 70, 38, RED);
                    break;
                case medium:
                    DrawRectangleLines(681, 285, 92, 38, RED);
                    break;
                case hard:
                    DrawRectangleLines(797, 285, 69, 38, RED);
                    break;
            }

            // Draw the unplayed game grid
            draw_grid_base();
        EndDrawing();

        if (startHandler(&dif)) session->game_started=1;
    }
    printf("starting\n");

    switch(dif)
    {
        case easy:
            *UPDATES_PER_SEC = 4;
            break;
        case medium:
            *UPDATES_PER_SEC = 6;
            break;
        case hard:
            *UPDATES_PER_SEC = 8;
            break;
    }
}

// Runs game logic when player prompts to begin.
void game_session_loop(sessionInfo* session, char* highScore, int* UPDATES_PER_SEC)
{
    clock_t time_update, new_time;
    bool input_lock = 0;
    while (session->game_started)
    {
        // Keep game paused while not in use
        while (!IsWindowMinimized);
        while (!IsWindowHidden);
        if (IsKeyPressed(KEY_ESCAPE) || WindowShouldClose()) CloseWindow();

        // Get time; will be checked for framerate
        time_update = clock();

        // Begin drawing on the GUI and perform logic
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Game in Progress", 220, 20, 18, BLACK);
            DrawText("High Score:", 675, 90, 24, BLACK);
            DrawText(highScore, 735-(6*strlen(highScore)), 130, 24, BLACK);
            game_logic(session, &input_lock);
            draw_grid_base();
            update_grid(session->head, session->fruit_loc);
        EndDrawing();

        // Enforce time update
        new_time = clock();
        while (difftime(new_time, time_update) < CLOCKS_PER_SEC/(*UPDATES_PER_SEC))
        {
            new_time = clock();
        }

        // Check again for clean inputs
        if (!input_lock) arrowKeyHandler(&(session->head->moving_dir));
        input_lock = !input_lock;
    }
}

/* Runs upon the player losing the game.
Player may press enter again to start another session. */
void game_over_loop(sessionInfo* session, char* highScore)
{
    // If high score achieved, write new score
    bool high_score_achieved = 0;
    uint64_t highscore_int = atoi(highScore);
    if (session->score > highscore_int)
    {
        FILE* windata;
        high_score_achieved = 1;
        sprintf(highScore, "%d", session->score);
        windata = fopen("data/windata.txt", "w");
        if (windata != NULL) fprintf(windata, highScore);
        fclose(windata);
    }

    enum difficulty dif = 1;
    while (!session->game_started)
    {
        if (IsKeyPressed(KEY_ESCAPE) || WindowShouldClose()) CloseWindow();

        // Draw game over screen; wait for exit or restart
        BeginDrawing();
            ClearBackground(RAYWHITE);
            draw_grid_base();
            update_grid(session->head, session->fruit_loc);
            DrawText("Game Over: Press ENTER to Return", 140, 20, 18, BLACK);
            if (high_score_achieved) DrawText("NEW HIGH SCORE!", 633, 90, 24, RED);
            else DrawText("High Score:", 675, 90, 24, BLACK);
            DrawText(highScore, 735-(6*strlen(highScore)), 130, 24, BLACK);
        EndDrawing();

        if (startHandler(&dif)) session->game_started = 1;
    }
}


/* //////////////////////////
//       MAIN METHOD       //
////////////////////////// */

int main(int argc, char** argv)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Snake Time");
    Image window_icon = LoadImage("data/snake.png");
    while(!IsImageReady(window_icon));
    SetWindowIcon(window_icon);

    // Initialize random number generator
    srand(time(NULL));

    // Read high score from file
    FILE* windata;
    windata = fopen("data/windata.txt", "r");
    char highScore[100];

    if (windata == NULL) strcat(highScore, "N/A");
    else fgets(highScore, 100, windata);
    fclose(windata);

    // Main running block
    while (1)
    {
        // Create session info
        plot* start_pos = malloc(sizeof(plot));
        *start_pos = (plot) { 0, 0 };
        snakePiece* head = malloc(sizeof(snakePiece));
        *head = (snakePiece) { start_pos, NULL, NULL, key_right };
        plot* fruit = getRandomPos(head);
        sessionInfo* session = malloc(sizeof(sessionInfo));
        *session = (sessionInfo) { head, NULL, fruit, 0, 0 };

        // Pre-Game block
        if (WindowShouldClose()) break;
        int UPDATES_PER_SEC;
        pre_game_loop(session, highScore, &UPDATES_PER_SEC);

        // Game playing block
        if (WindowShouldClose()) break;
        game_session_loop(session, highScore, &UPDATES_PER_SEC);
        
        // Game over block
        if (WindowShouldClose()) break;
        game_over_loop(session, highScore);
    }

    return 0;
}
