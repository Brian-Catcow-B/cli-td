#include "enemy.h"

static const int lut_enemy_hps[] = {
	10,
	20,
};

static const char lut_enemy_letters[] = {
	'a',
	'b',
};

void init_enemy(enemy_t *self, e_enemy_type type, board_t *board) {
	self->type = type;
	self->board = board;

	self->pos.x = -1;
	self->pos.y = -1;
	self->hp = lut_enemy_hps[type];
	self->letter = lut_enemy_letters[type];
}

void deinit_enemy(enemy_t *self) {

}
