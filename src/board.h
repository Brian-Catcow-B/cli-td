#ifndef BOARD_H
#define BOARD_H

#define BOARD_WIDTH 80
#define BOARD_HEIGHT 40

#include <stddef.h>

typedef struct board_position_t {
	int y;
	int x;
} board_position_t;

typedef enum e_path_direction {
	e_path_direction_none,
	e_path_direction_left,
	e_path_direction_right,
	e_path_direction_up,
	e_path_direction_down,
} e_path_direction;

char arrow_from_path_direction(e_path_direction direction);

typedef enum e_tile_type {
	e_tile_type_vacant,
	e_tile_type_path,
	e_tile_type_tower,
} e_tile_type;

typedef struct tile_t {
	e_tile_type type;
	e_path_direction path_direction;
	struct enemy_t *enemy_on;
	size_t y;
	size_t x;
} tile_t;

void init_tile(tile_t *self, board_position_t bp);
void deinit_tile(tile_t *self);
char tile_char(tile_t *self);
void tile_update(tile_t *self);

typedef struct board_t {
	tile_t tiles[BOARD_HEIGHT][BOARD_WIDTH];
} board_t;

void init_board(board_t *self);
void deinit_board(board_t *self);
void generate_path(board_t *self);

#endif // BOARD_H

