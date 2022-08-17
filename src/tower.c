#include "tower.h"
#include "board.h"

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

void init_tower(tower_t *self, struct board_t *board, pos2d_t pos, e_tower_type type) {
	self->type = type;
	self->level = 1;
	self->board = board;
	self->pos = pos;
	init_pos2d_vec(&ordered_path_tiles_in_range);
	self->frames_until_shot = shot_cooldown_from_tower_type(self->type);

void deinit_tower(tower_t *self) {
	deinit_pos2d_vec(&ordered_path_in_range);
}

