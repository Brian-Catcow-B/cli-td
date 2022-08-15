#include "board.h"
#include <stdlib.h>
#include <ncurses.h>
#include "enemy.h"

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
	board_tile_update(self);
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
			return 'T';
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
	pos2d_t bp;
	for (size_t x = 0; x < BOARD_WIDTH; x++) {
		for (size_t y = 0; y < BOARD_HEIGHT; y++) {
			bp.y = y;
			bp.x = x;
			init_board_tile(&(self->tiles[y][x]), bp, self);
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

void generate_path(board_t *self) {
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

