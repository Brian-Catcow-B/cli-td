#include "board.h"
#include <stdlib.h>
#include <ncurses.h>
#include "enemy.h"
#include "tower.h"

#include "log.h"

char arrow_from_path_direction(e_board_path_direction direction) {
	switch (direction) {
		case e_board_path_direction_left:
			return '<';
		case e_board_path_direction_right:
			return '>';
		case e_board_path_direction_up:
			return '^';
		case e_board_path_direction_down:
			return 'v';
		default:
			return '!';
	}
}

// ======================================================
// BOARD_TILE_T
// ======================================================

void init_board_tile(board_tile_t *self, pos2d_t bp, board_t *board) {
	self->type = e_board_tile_type_vacant;
	self->path_direction = e_board_path_direction_none;
	self->enemy_on = NULL;
	self->x = bp.x;
	self->y = bp.y;
	self->board = board;
	self->custom_char = '?';
}

void deinit_board_tile(board_tile_t *self) {

}

char board_tile_char(board_tile_t *self) {
	switch (self->type) {
		case e_board_tile_type_vacant:
			return ' ';
		case e_board_tile_type_path:
			if (self->enemy_on == NULL)
			{
				return arrow_from_path_direction(self->path_direction);
			}
			else
			{
				return self->enemy_on->letter;
			}
		case e_board_tile_type_tower:
			return self->custom_char;
		default:
			return '!';
	}
}

void board_tile_set_path(board_tile_t *self, e_board_path_direction direction) {
	self->type = e_board_tile_type_path;
	self->path_direction = direction;
}

void board_tile_set_path_and_update(board_tile_t *self, e_board_path_direction direction) {
	board_tile_set_path(self, direction);
	board_tile_update(self);
}

void board_tile_update(board_tile_t *self) {
	mvaddch(self->y + self->board->origin_offset.y, self->x + self->board->origin_offset.x, board_tile_char(self));
}

// ======================================================
// BOARD_T
// ======================================================

void init_board(board_t *self, pos2d_t oo) {
	for (size_t x = 0; x < BOARD_WIDTH; x++) {
		for (size_t y = 0; y < BOARD_HEIGHT; y++) {
			init_board_tile(&(self->tiles[y][x]), pos2d(y, x), self);
		}
	}
	self->enemy_start_pos.y = -1;
	self->enemy_start_pos.x = -1;
	self->origin_offset.y = oo.y;
	self->origin_offset.x = oo.x;
}

void deinit_board(board_t *self) {
	for (size_t x = BOARD_BORDER_L; x < BOARD_WIDTH + BOARD_BORDER_L; x++) {
		for (size_t y = BOARD_BORDER_U; y < BOARD_HEIGHT + BOARD_BORDER_U; y++) {
			deinit_board_tile(&(self->tiles[y][x]));
		}
	}
}

void board_generate_path(board_t *self) {
	self->enemy_start_pos.y = 0;
	self->enemy_start_pos.x = 2;
	for (size_t y = 0; y < BOARD_HEIGHT - 3; y++) {
		board_tile_set_path_and_update(&(self->tiles[y][2]), e_board_path_direction_down);
	}

	for (size_t x = 2; x < BOARD_WIDTH - 3; x++) {
		board_tile_set_path_and_update(&(self->tiles[BOARD_HEIGHT - 3][x]), e_board_path_direction_right);
	}

	for (size_t y = 0; y < BOARD_HEIGHT - 2; y++) {
		board_tile_set_path_and_update(&(self->tiles[y][BOARD_WIDTH - 3]), e_board_path_direction_up);
	}
}

void board_update_all(board_t *self) {
	for (size_t y = 0; y < BOARD_HEIGHT; y++)
		for (size_t x = 0; x < BOARD_WIDTH; x++)
			board_tile_update(&(self->tiles[y][x]));
}

bool board_is_area_valid_tower_placement(board_t *self, pos2d_t top_left, int height, int width) {
	for (int y = top_left.y; y < top_left.y + height; y++) {
		for (int x = top_left.x; x < top_left.x + width; x++) {
			switch (self->tiles[y][x].type) {
				case e_board_tile_type_vacant:
					break;
				default:
					return false;
			}
		}
	}
	return true;
}

bool board_place_tower(board_t *self, struct tower_t *tower) {
	if (!board_is_area_valid_tower_placement(self, tower->origin, tower->height, tower->width))
		return false;
	
	board_tile_t *tile;
	for (int yoff = 0; yoff < tower->height; yoff++) {
		for (int xoff = 0; xoff < tower->height; xoff++) {
			tile = &(self->tiles[yoff + tower->origin.y][xoff + tower->origin.x]);
			tile->type = e_board_tile_type_tower;
			tile->custom_char = tower->chars[yoff][xoff];
		}
	}

	return true;
}
