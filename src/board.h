#ifndef BOARD_H
#define BOARD_H

#include <stddef.h>

#define WINDOW_WIDTH 80
#define WINDOW_HEIGHT 30

#define BOARD_BORDER_L 1
#define BOARD_BORDER_R 1
#define BOARD_BORDER_U 1
#define BOARD_BORDER_D 1

#define BOARD_WIDTH (WINDOW_WIDTH - BOARD_BORDER_L - BOARD_BORDER_R)
#define BOARD_HEIGHT (WINDOW_HEIGHT - BOARD_BORDER_U - BOARD_BORDER_D)

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

typedef enum e_border_direction {
	e_border_direction_none,
	e_border_direction_horizontal,
	e_border_direction_vertical,
	e_border_direction_multi,
} e_border_direction;

char line_from_border_direction(e_border_direction direction);

typedef enum e_tile_type {
	e_tile_type_vacant,
	e_tile_type_path,
	e_tile_type_tower,
	e_tile_type_border,
} e_tile_type;

typedef struct tile_t {
	e_tile_type type;
	e_path_direction path_direction;
	e_border_direction border_direction;
	struct enemy_t *enemy_on;
	size_t y;
	size_t x;
} tile_t;

void init_tile(tile_t *self, board_position_t bp);
void deinit_tile(tile_t *self);
char tile_char(tile_t *self);
void tile_update(tile_t *self);
void tile_set_path(tile_t *self, e_path_direction direction);
void tile_set_path_and_update(tile_t *self, e_path_direction direction);
void tile_set_border(tile_t *self, e_border_direction direction);
void tile_set_border_and_update(tile_t *self, e_border_direction direction);

typedef struct board_t {
	tile_t tiles[WINDOW_HEIGHT][WINDOW_WIDTH];
	board_position_t enemy_start_pos;
} board_t;

void init_board(board_t *self);
void deinit_board(board_t *self);
void generate_path(board_t *self);
void generate_border(board_t *self);

#endif // BOARD_H

