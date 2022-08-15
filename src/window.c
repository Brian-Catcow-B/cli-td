#include "window.h"
#include <ncurses.h>

// priv decls

// window_tile_t

char line_from_border_direction(e_border_direction direction);
void window_tile_set_border(window_tile_t *self, e_border_direction direction);

// pub defns

// window_t

void init_window(window_t *self) {
	init_board(&(self->board), pos2d(BOARD_BORDER_U, BOARD_BORDER_L));
	board_generate_path(&(self->board));
	for (size_t y = 0; y < WINDOW_HEIGHT; y++) {
		for (size_t x = 0; x < WINDOW_WIDTH; x++) {
			init_window_tile(&(self->tiles[y][x]), pos2d(y, x));
		}
	}
}

void window_generate_board_border(window_t *self) {
	for (size_t y = BOARD_BORDER_U - 1; y < BOARD_BORDER_U + BOARD_HEIGHT + 1; y++) {
		window_tile_set_border(&(self->tiles[y][BOARD_BORDER_L - 1]), e_border_direction_vertical);
		window_tile_set_border(&(self->tiles[y][BOARD_BORDER_L + BOARD_WIDTH]), e_border_direction_vertical);
	}

	for (size_t x = BOARD_BORDER_L - 1; x < BOARD_BORDER_L + BOARD_WIDTH + 1; x++) {
		window_tile_set_border(&(self->tiles[BOARD_BORDER_U - 1][x]), e_border_direction_horizontal);
		window_tile_set_border(&(self->tiles[BOARD_BORDER_U + BOARD_HEIGHT][x]), e_border_direction_horizontal);
	}
}

void window_pos_update(window_t *self, pos2d_t pos) {
	mvaddch(pos.y, pos.x, window_pos_char(self, pos));
}

char window_pos_char(window_t *self, pos2d_t pos) {
	switch (self->tiles[pos.y][pos.x].type) {
		case e_window_tile_type_none:
			return ' ';
		case e_window_tile_type_board:
			return board_tile_char(&(self->board.tiles[pos.y - self->board.origin_offset.y][pos.x - self->board.origin_offset.x]));
		case e_window_tile_type_border:
			return line_from_border_direction(self->tiles[pos.y][pos.x].border_direction);
		default:
			return '?';
	}
}

// priv defns

// window_tile_t

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

void init_window_tile(window_tile_t *self, pos2d_t pos) {
	self->type = e_window_tile_type_none;
	self->border_direction = e_border_direction_none;
	self->x = pos.x;
	self->y = pos.y;
}

void window_tile_set_border(window_tile_t *self, e_border_direction direction) {
	if (self->type == e_window_tile_type_border && self->border_direction != direction)
		direction = e_border_direction_multi;
	self->type = e_window_tile_type_border;
	self->border_direction = direction;
}

