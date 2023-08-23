
#include "key_handler.h"
#include <raylib.h>
#include <stdio.h>

void arrowKeyHandler(enum direction* key_pressed)
{
    if (IsKeyPressed)
    {
        int tempKey = GetKeyPressed();
        switch (tempKey)
        {
            case KEY_UP:
                *key_pressed = key_up;
                break;
            case KEY_DOWN:
                *key_pressed = key_down;
                break;
            case KEY_LEFT:
                *key_pressed = key_left;
                break;
            case KEY_RIGHT:
                *key_pressed = key_right;
                break;
        }
    }
}

bool startHandler()
{
    if (IsKeyPressed)
    {
        int tempKey = GetKeyPressed();
        if (tempKey==KEY_ENTER) return true;
    }
    return false;
}
