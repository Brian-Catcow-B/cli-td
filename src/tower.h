#ifndef TOWER_H
#define TOWER_H

#include "pos2d.h"

typedef enum e_tower_type {
	e_tower_type_rocket,
	e_tower_type_laser,
	e_tower_type_cat,
} e_tower_type;

char center_char_from_tower_type(e_tower_type type, int level);

typedef struct tower_t {
	e_tower_type type;
	int level;
	struct board_t *board;
	pos2d_t pos;
	pos2d_vec_t ordered_path_tiles_in_range;
	int frames_until_shot;
	struct enemy_t *target;
} tower_t;

void init_tower(tower_t *self, struct board_t *board, pos2d_t pos, e_tower_type type);
void deinit_tower(tower_t *self);

#endif // TOWER_H

