#include "board.h"
#include <stdlib.h>
#include <ncurses.h>

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

void init_tile(tile_t *self, board_position_t bp) {
	self->type = e_tile_type_vacant;
	self->path_direction = e_path_direction_none;
	self->enemy_on = NULL;
	self->x = bp.x;
	self->y = bp.y;
	tile_update(self);
}

void deinit_tile(tile_t *self) {

}

char tile_char(tile_t *self) {
	switch (self->type) {
		case e_tile_type_vacant:
			return '.';
		case e_tile_type_path:
			return arrow_from_path_direction(self->path_direction);
		case e_tile_type_tower:
			return 'T';
		default:
			return '!';
	}
}

void tile_update(tile_t *self) {
	mvaddch(self->y, self->x, tile_char(self));
}

void init_board(board_t *self) {
	board_position_t bp;
	for (size_t x = 0; x < BOARD_WIDTH; x++) {
		for (size_t y = 0; y < BOARD_HEIGHT; y++) {
			bp.y = y;
			bp.x = x;
			init_tile(&(self->tiles[y][x]), bp);
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

void generate_path(board_t *self) {
	for (size_t y = 0; y < BOARD_HEIGHT - 3; y++) {
		self->tiles[y][2].type = e_tile_type_path;
		self->tiles[y][2].path_direction = e_path_direction_down;
	}

	for (size_t x = 2; x < BOARD_WIDTH - 3; x++) {
		self->tiles[BOARD_HEIGHT - 2][x].type = e_tile_type_path;
		self->tiles[BOARD_HEIGHT - 2][x].path_direction = e_path_direction_right;
	}

	for (size_t y = 0; y < BOARD_HEIGHT - 2; y++) {
		self->tiles[y][BOARD_WIDTH - 2].type = e_tile_type_path;
		self->tiles[y][BOARD_WIDTH - 2].path_direction = e_path_direction_up;
	}
}

