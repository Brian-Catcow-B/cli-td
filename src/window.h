#ifndef WINDOW_H
#define WINDOW_H

#include "board.h"
#include "pos2d.h"
#include "dims.h"

typedef enum e_window_tile_type {
	e_window_tile_type_none;
	e_window_tile_type_border;
	e_window_tile_type_board;
} e_window_tile_type;

typedef struct window_tile_t {
	e_window_tile_type type;
} window_tile_t;

typedef struct window_t {
	window_tile_t tiles[WINDOW_HEIGHT][WINDOW_WIDTH];
	board_t board;
} window_t;

void init_window(window_t *self);
void window_generate_board_border(window_t *self);

#endif // WINDOW_H

