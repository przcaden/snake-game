
#include "key_handler.h"
#include <raylib.h>
#include <stdio.h>

void arrowKeyHandler(enum direction* moving_dir)
{
    enum direction key_pressed = *moving_dir;
    if (IsKeyPressed)
    {
        // Get the current key pressed
        int tempKey = GetKeyPressed();
        switch (tempKey)
        {
            case KEY_UP:
                key_pressed = key_up;
                break;
            case KEY_DOWN:
                key_pressed = key_down;
                break;
            case KEY_LEFT:
                key_pressed = key_left;
                break;
            case KEY_RIGHT:
                key_pressed = key_right;
                break;
        }

        // Prevent the player from moving backwards
        if (key_pressed == key_left && *moving_dir == key_right ||
            key_pressed == key_right && *moving_dir == key_left ||
            key_pressed == key_up && *moving_dir == key_down ||
            key_pressed == key_down && *moving_dir == key_up)
            return;
        *moving_dir = key_pressed;
    }
}

bool startHandler(enum difficulty* dif)
{
    if (IsKeyPressed)
    {
        int tempKey = GetKeyPressed();
        switch (tempKey)
        {
            case KEY_LEFT:
                if (*dif == medium) *dif = easy;
                else if (*dif == hard) *dif = medium;
                break;
            case KEY_RIGHT:
                if (*dif == medium) *dif = hard;
                else if (*dif == easy) *dif = medium;
                break;
            case KEY_ENTER:
                return true;
                break;
        }
    }
    return false;
}
