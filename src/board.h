#ifndef BOARD_H
#define BOARD_H

#include <stddef.h>
#include "pos2d.h"
#include "dims.h"

typedef enum e_board_path_direction {
	e_board_path_direction_none,
	e_board_path_direction_left,
	e_board_path_direction_right,
	e_board_path_direction_up,
	e_board_path_direction_down,
} e_board_path_direction;

char arrow_from_path_direction(e_board_path_direction direction);

typedef enum e_board_tile_type {
	e_board_tile_type_vacant,
	e_board_tile_type_path,
	e_board_tile_type_tower,
	e_board_tile_type_border,
} e_board_tile_type;

typedef struct board_tile_t {
	struct board_t *board;
	e_board_tile_type type;
	e_board_path_direction path_direction;
	struct enemy_t *enemy_on;
	size_t y;
	size_t x;
} board_tile_t;

void init_tile(board_tile_t *self, pos2d_t bp);
void deinit_tile(board_tile_t *self);
char board_tile_char(board_tile_t *self);
void board_tile_update(board_tile_t *self);
void board_tile_set_path(board_tile_t *self, e_board_path_direction direction);
void board_tile_set_path_and_update(board_tile_t *self, e_board_path_direction direction);

typedef struct board_t {
	board_tile_t tiles[BOARD_HEIGHT][BOARD_WIDTH];
	pos2d_t enemy_start_pos;
	pos2d_t origin_offset;
} board_t;

void init_board(board_t *self, pos2d_t oo);
void deinit_board(board_t *self);
void generate_path(board_t *self);

#endif // BOARD_H

