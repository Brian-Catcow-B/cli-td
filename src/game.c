#include "game.h"
#include <ncurses.h>
#include <stdlib.h>
#include "data_structures.h"
#include "enemy.h"
#include "log.h"

void init_context(context_t *self) {
	init_board(&(self->board));
	generate_path(&(self->board));
	self->vec_enemies = alloc_init_vector();
}

void deinit_context(context_t *self) {
	size_t size = vector_size(self->vec_enemies);
	for (size_t i = 0; i < size; i++) {
		void *elem = vector_at(self->vec_enemies, i);
		free(elem);
	}
	dealloc_deinit_vector(self->vec_enemies);
}

bool handle_key_press(context_t *c, int ch);
void game_loop() {
	context_t c;
	init_context(&c);
	while (1) {
		if (handle_key_press(&c, getch()))
			break;
	}
	deinit_context(&c);
}

bool handle_key_press(context_t *c, int ch) {
	switch (ch) {
		case 'q':
			return true;
		case 's': {
			enemy_t *new_enemy = alloc_init_enemy(e_enemy_type_a, &(c->board));
			enemy_set_pos(new_enemy, c->board.enemy_start_pos);
			vector_push_back(c->vec_enemies, new_enemy);
			break;
		}
	}

	return false;
}

