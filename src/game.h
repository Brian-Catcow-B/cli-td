#ifndef GAME_H
#define GAME_H

#include "board.h"

typedef struct context_t {
	board_t board;
} context_t;

void init_context(context_t *self);
void deinit_context(context_t *self);

void game_loop();

#endif // GAME_H

