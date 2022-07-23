#ifndef BOARD_H
#define BOARD_H

#define BOARD_WIDTH 1
#define BOARD_HEIGHT 50

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
} tile_t;

void init_tile(tile_t *self);
void deinit_tile(tile_t *self);

typedef struct board_t {
	tile_t tiles[BOARD_HEIGHT][BOARD_WIDTH];
} board_t;

void init_board(board_t *self);
void deinit_board(board_t *self);

typedef struct board_position_t {
	int y;
	int x;
} board_position_t;

#endif // BOARD_H

