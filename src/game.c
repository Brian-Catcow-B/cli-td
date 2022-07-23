#include "game.h"
#include <ncurses.h>

void init_context(context_t *self) {
	init_board(&self->board);
	generate_path(&self->board);
}

void deinit_context(context_t *self) {

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
	if (ch == 'q')
		return true;

	return false;
}

