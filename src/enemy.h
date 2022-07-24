#ifndef ENEMY_H
#define ENEMY_H

#include "board.h"

typedef enum e_enemy_type {
	e_enemy_type_a,
	e_enemy_type_b,
} e_enemy_type;

typedef struct enemy_t {
	e_enemy_type type;
	int hp;
	char letter;
	board_position_t pos;
	board_t *board;
} enemy_t;

enemy_t *alloc_init_enemy(e_enemy_type type, board_t *board);
void init_enemy(enemy_t *self, e_enemy_type type, board_t *board);
void dealloc_deinit_enemy(enemy_t *self);
void deinit_enemy(enemy_t *self);

void enemy_set_pos(enemy_t *self, board_position_t new_pos);

#endif // ENEMY_H

