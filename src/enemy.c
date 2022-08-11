#include "enemy.h"
#include <stdlib.h>
#include "log.h"
#include "board.h"

static const int lut_enemy_hps[] = {
	10,
	20,
};

static const char lut_enemy_letters[] = {
	'A',
	'B',
};

static const int lut_enemy_update_frames[] = {
	30,
	35,
};

enemy_t *alloc_init_enemy(e_enemy_type type, board_t *board) {
	enemy_t *retval = malloc(sizeof(enemy_t));
	init_enemy(retval, type, board);
	return retval;
}

void init_enemy(enemy_t *self, e_enemy_type type, board_t *board) {
	self->type = type;
	self->board = board;
	self->frames_until_update = lut_enemy_update_frames[type];

	self->pos.x = -1;
	self->pos.y = -1;
	self->hp = lut_enemy_hps[type];
	self->letter = lut_enemy_letters[type];
}

void dealloc_deinit_enemy(enemy_t *self) {
	deinit_enemy(self);
	free(self);
}

void deinit_enemy(enemy_t *self) {

}

void enemy_set_pos(enemy_t *self, pos2d_t new_pos) {
	if (self->pos.x >= 0 && self->pos.x < BOARD_WIDTH && self->pos.y >= 0 && self->pos.y < BOARD_HEIGHT) {
		tile_t *current_tile = &(self->board->tiles[self->pos.y][self->pos.x]);
		current_tile->enemy_on = NULL;
		tile_update(current_tile);
	}

	self->pos = new_pos;

	if (self->pos.x >+ 0 && self->pos.x < BOARD_WIDTH && self->pos.y >= 0 && self->pos.y < BOARD_HEIGHT) {
		tile_t *new_tile = &(self->board->tiles[self->pos.y][self->pos.x]);
		new_tile->enemy_on = self;
		tile_update(new_tile);
	}
}

void enemy_update(enemy_t *self) {
	self->frames_until_update--;
	if (self->frames_until_update > 0) {
		return;
	}

	self->frames_until_update = lut_enemy_update_frames[self->type];
	tile_t *current_tile = &(self->board->tiles[self->pos.y][self->pos.x]);
	pos2d_t next_pos = self->pos;
	switch (current_tile->path_direction) {
		case e_path_direction_left:
			next_pos.x--;
			break;
		case e_path_direction_right:
			next_pos.x++;
			break;
		case e_path_direction_up:
			next_pos.y--;
			break;
		case e_path_direction_down:
			next_pos.y++;
			break;
		default:
			break;
	}
	enemy_set_pos(self, next_pos);
}

