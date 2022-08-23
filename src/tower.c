#include "tower.h"
#include "board.h"
#include "integral_math.h"

#include <assert.h>
#include <stdio.h>

char center_char_from_tower_type(e_tower_type type, int level) {
	switch (type) {
		case e_tower_type_rocket:
			return (level < 3) ? 'r' : 'R';
		case e_tower_type_laser:
			return (level < 3) ? 'l' : 'L';
		case e_tower_type_cat:
			return (level < 3) ? 'c' : 'C';
		default:
			return '?';
	}
}

int range_from_tower_type(e_tower_type type, int level) {
	switch (type) {
		case e_tower_type_rocket:
			return 5 + level;
		case e_tower_type_laser:
			return 4 + level;
		case e_tower_type_cat:
			return 3 + (level / 2);
	}
	assert(0);
	return -1;
}

int shot_cooldown_from_tower_type(e_tower_type type, int level) {
	switch (type) {
		case e_tower_type_rocket:
			return 90;
		case e_tower_type_laser:
			return 20;
		case e_tower_type_cat:
			return 120 - ((level - 1) * 20);
	}
	assert(0);
	return -1;
}

void init_and_fill_ordered_path_tiles(tower_t *tower) {
	init_pos2d_vec(&(tower->ordered_path_tiles_in_range), 20);
	pos2d_t current_pos = tower->board->enemy_start_pos;
	while (current_pos.y >= 0 && current_pos.y < BOARD_HEIGHT
		&& current_pos.x >= 0 && current_pos.x < BOARD_WIDTH) {
		int x_diff = (current_pos.x < tower->pos.x) ? tower->pos.x - current_pos.x : current_pos.x - tower->pos.x;
		int y_diff = (current_pos.y < tower->pos.y) ? tower->pos.y - current_pos.y : current_pos.y - tower->pos.y;
		int range = range_from_tower_type(tower->type, tower->level);
		if (integral_sqrt_rn(x_diff * x_diff + y_diff * y_diff) >= range)
			pos2d_vec_push_back(&(tower->ordered_path_tiles_in_range), current_pos);
		switch (tower->board->tiles[current_pos.y][current_pos.x].path_direction) {
			case e_board_path_direction_up:
				current_pos.y--;
				break;
			case e_board_path_direction_right:
				current_pos.x++;
				break;
			case e_board_path_direction_down:
				current_pos.y++;
				break;
			case e_board_path_direction_left:
				current_pos.x--;
				break;
			default:
				printf("unexpected e_board_path_direction in init_and_fill_ordered_path_tiles: %d\n", tower->board->tiles[current_pos.y][current_pos.x].path_direction);
				return;
		}
	}
}

void init_tower(tower_t *self, struct board_t *board, pos2d_t pos, e_tower_type type) {
	self->type = type;
	self->level = 1;
	self->board = board;
	self->pos = pos;
	init_and_fill_ordered_path_tiles(self);
	self->frames_until_shot = shot_cooldown_from_tower_type(self->type, self->level);
}

void deinit_tower(tower_t *self) {
	deinit_pos2d_vec(&(self->ordered_path_tiles_in_range));
}

