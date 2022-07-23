#include <ncursesw/ncurses.h>
#include <stdio.h>

#include "game.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

void init_ncurses();
void deinit_ncurses();

int main(int argc, char **argv) {
	init_ncurses();

	//printw("Hello World !!!");
	//refresh();
	//int ch = getch();
	
	//printw("key pressed is ");
	//attron(A_BOLD);
	//printw("%c", ch);
	//attroff(A_BOLD);

	//getch();
	
	game_loop();

	deinit_ncurses();
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

