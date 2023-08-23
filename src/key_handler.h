
#ifndef KEY_HANDLER_H_
#define KEY_HANDLER_H_

#include <stdbool.h>

enum direction { key_up, key_down, key_left, key_right };
void arrowKeyHandler(enum direction* moving_dir);
bool startHandler();

#endif
