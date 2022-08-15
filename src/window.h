#ifndef WINDOW_H
#define WINDOW_H

#include "board.h"
#include "pos2d.h"
#include "dims.h"

typedef enum e_window_tile_type {
	e_window_tile_type_none,
	e_window_tile_type_border,
	e_window_tile_type_board,
} e_window_tile_type;

typedef enum e_border_direction {
	e_border_direction_none,
	e_border_direction_horizontal,
	e_border_direction_vertical,
	e_border_direction_multi,
} e_border_direction;

typedef struct window_tile_t {
	e_window_tile_type type;
	e_border_direction border_direction;
	size_t y;
	size_t x;
} window_tile_t;

void init_window_tile(window_tile_t *self, pos2d_t pos);
void window_tile_update(window_tile_t *self);

typedef struct window_t {
	window_tile_t tiles[WINDOW_HEIGHT][WINDOW_WIDTH];
	board_t board;
} window_t;

void init_window(window_t *self);
void window_generate_board_border(window_t *self);
void window_pos_update(window_t *self, pos2d_t pos);
char window_pos_char(window_t *self, pos2d_t pos);

#endif // WINDOW_H

