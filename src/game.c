#include "game.h"
#include <ncurses.h>
#include <stdlib.h>
#include "data_structures.h"
#include "enemy.h"
#include "log.h"

#define FPS 60

void init_context(context_t *self) {
	init_board(&(self->board));
	generate_path(&(self->board));
	generate_border(&(self->board));
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
void update_game(context_t *c);
void game_loop() {
	context_t c;
	init_context(&c);
	timeout(1000 / FPS);
	curs_set(0);
	while (1) {
		int ch = getch();
		if (ch != -1)
		{
			if (handle_key_press(&c, ch))
			{
				break;
			}
		}
		else
		{
			update_game(&c);
		}
	}
	deinit_context(&c);
}

bool handle_key_press(context_t *c, int ch) {
	switch (ch) {
		case 'q':
			return true;
		case 'a': {
			enemy_t *new_enemy = alloc_init_enemy(e_enemy_type_a, &(c->board));
			enemy_set_pos(new_enemy, c->board.enemy_start_pos);
			vector_push_back(c->vec_enemies, new_enemy);
			break;
		}
		case 'b': {
			enemy_t *new_enemy = alloc_init_enemy(e_enemy_type_b, &(c->board));
			enemy_set_pos(new_enemy, c->board.enemy_start_pos);
			vector_push_back(c->vec_enemies, new_enemy);
			break;
		}
	}

	return false;
}

void update_game(context_t *c) {
	size_t num_enemies = vector_size(c->vec_enemies);
	for (size_t i = 0; i < num_enemies; i++)
	{
		enemy_t *current_enemy = vector_at(c->vec_enemies, i);
		enemy_update(current_enemy);
	}
}

