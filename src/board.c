#include "board.h"
#include <stdlib.h>

char arrow_from_path_direction(e_path_direction direction) {
	switch (direction) {
		case e_path_direction_left:
			return '<';
		case e_path_direction_right:
			return '>';
		case e_path_direction_up:
			return '^';
		case e_path_direction_down:
			return 'v';
		default:
			return '!';
	}
}

void init_tile(tile_t *self) {
	self->type = e_tile_type_vacant;
	self->path_direction = e_path_direction_none;
	self->enemy_on = NULL;
}

void deinit_tile(tile_t *self) {

}

void init_board(board_t *self) {
	for (size_t x = 0; x < BOARD_WIDTH; x++) {
		for (size_t y = 0; y < BOARD_HEIGHT; y++) {
			init_tile(&(self->tiles[y][x]));
		}
	}
}

void deinit_board(board_t *self) {
	for (size_t x = 0; x < BOARD_WIDTH; x++) {
		for (size_t y = 0; y < BOARD_HEIGHT; y++) {
			deinit_tile(&(self->tiles[y][x]));
		}
	}
}

