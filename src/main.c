#include <ncursesw/ncurses.h>
#include <stdio.h>

#include "game.h"
#include "log.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

void init_ncurses();
void deinit_ncurses();

int main() {
	open_log_file();
	LOG("===\nPROGRAM START\n===\n");
	init_ncurses();

	game_loop();

	deinit_ncurses();
	LOG("===\nPROGRAM CLEAN FINISH\n===\n");
	close_log_file();
	return EXIT_SUCCESS;
}

void init_ncurses() {
	initscr();
	raw();
	keypad(stdscr, true);
	noecho();
}

void deinit_ncurses() {
	endwin();
}

