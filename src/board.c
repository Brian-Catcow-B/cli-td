#include "board.h"
#include <stdlib.h>
#include <ncurses.h>
#include "enemy.h"

#include "log.h"

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

char line_from_border_direction(e_border_direction direction) {
	switch (direction) {
		case e_border_direction_horizontal:
			return '-';
		case e_border_direction_vertical:
			return '|';
		case e_border_direction_multi:
			return '+';
		default:
			return '!';
	}
}

void init_tile(tile_t *self, board_position_t bp) {
	self->type = e_tile_type_vacant;
	self->path_direction = e_path_direction_none;
	self->border_direction = e_border_direction_none;
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
			return ' ';
		case e_tile_type_path:
			if (self->enemy_on == NULL)
			{
				return arrow_from_path_direction(self->path_direction);
			}
			else
			{
				return self->enemy_on->letter;
			}
		case e_tile_type_tower:
			return 'T';
		case e_tile_type_border:
			return line_from_border_direction(self->border_direction);
		default:
			return '!';
	}
}

void tile_set_path(tile_t *self, e_path_direction direction) {
	self->type = e_tile_type_path;
	self->path_direction = direction;
}

void tile_set_path_and_update(tile_t *self, e_path_direction direction) {
	tile_set_path(self, direction);
	tile_update(self);
}

void tile_set_border(tile_t *self, e_border_direction direction) {
	e_border_direction combined_direction = direction;
	if (self->type == e_tile_type_border && self->border_direction != direction)
		combined_direction = e_border_direction_multi;
	self->type = e_tile_type_border;
	self->border_direction = combined_direction;
}

void tile_set_border_and_update(tile_t *self, e_border_direction direction) {
	tile_set_border(self, direction);
	tile_update(self);
}

void tile_update(tile_t *self) {
	mvaddch(self->y, self->x, tile_char(self));
}

void init_board(board_t *self) {
	board_position_t bp;
	for (size_t x = 0; x < WINDOW_WIDTH; x++) {
		for (size_t y = 0; y < WINDOW_HEIGHT; y++) {
			bp.y = y;
			bp.x = x;
			init_tile(&(self->tiles[y][x]), bp);
		}
	}
	self->enemy_start_pos.y = -1;
	self->enemy_start_pos.x = -1;
}

void deinit_board(board_t *self) {
	for (size_t x = BOARD_BORDER_L; x < BOARD_WIDTH + BOARD_BORDER_L; x++) {
		for (size_t y = BOARD_BORDER_U; y < BOARD_HEIGHT + BOARD_BORDER_U; y++) {
			deinit_tile(&(self->tiles[y][x]));
		}
	}
}

void generate_path(board_t *self) {
	self->enemy_start_pos.y = BOARD_BORDER_U + 0;
	self->enemy_start_pos.x = BOARD_BORDER_L + 2;
	for (size_t y = BOARD_BORDER_U; y < BOARD_HEIGHT + BOARD_BORDER_U - 3; y++) {
		tile_set_path_and_update(&(self->tiles[y][BOARD_BORDER_L + 2]), e_path_direction_down);
	}

	for (size_t x = BOARD_BORDER_L + 2; x < BOARD_WIDTH + BOARD_BORDER_L - 3; x++) {
		tile_set_path_and_update(&(self->tiles[BOARD_HEIGHT + BOARD_BORDER_U - 3][x]), e_path_direction_right);
	}

	for (size_t y = BOARD_BORDER_U; y < BOARD_HEIGHT + BOARD_BORDER_U - 2; y++) {
		tile_set_path_and_update(&(self->tiles[y][BOARD_WIDTH + BOARD_BORDER_L - 3]), e_path_direction_up);
	}
}

void generate_border(board_t *self) {
	for (size_t y = BOARD_BORDER_U - 1; y < BOARD_BORDER_U + BOARD_HEIGHT + 1; y++) {
		tile_set_border_and_update(&(self->tiles[y][BOARD_BORDER_L - 1]), e_border_direction_vertical);
		tile_set_border_and_update(&(self->tiles[y][BOARD_BORDER_L + BOARD_WIDTH]), e_border_direction_vertical);
	}

	for (size_t x = BOARD_BORDER_L - 1; x < BOARD_BORDER_L + BOARD_WIDTH + 1; x++) {
		tile_set_border_and_update(&(self->tiles[BOARD_BORDER_U - 1][x]), e_border_direction_horizontal);
		tile_set_border_and_update(&(self->tiles[BOARD_BORDER_U + BOARD_HEIGHT][x]), e_border_direction_horizontal);
	}
}

