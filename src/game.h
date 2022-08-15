#ifndef GAME_H
#define GAME_H

#include "window.h"

typedef struct context_t {
	window_t window;
	struct vector_t *vec_enemies;
} context_t;

void init_context(context_t *self);
void deinit_context(context_t *self);

void game_loop();

#endif // GAME_H

