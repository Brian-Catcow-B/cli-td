#include "window.h"

void window_generate_board_border(window_t *self) {
	for (size_t y = BOARD_BORDER_U - 1; y < BOARD_BORDER_U + BOARD_HEIGHT + 1; y++) {
		tile_set_border_and_update(&(self->tiles[y][BOARD_BORDER_L - 1]), e_border_direction_vertical);
		tile_set_border_and_update(&(self->tiles[y][BOARD_BORDER_L + BOARD_WIDTH]), e_border_direction_vertical);
	}

	for (size_t x = BOARD_BORDER_L - 1; x < BOARD_BORDER_L + BOARD_WIDTH + 1; x++) {
		tile_set_border_and_update(&(self->tiles[BOARD_BORDER_U - 1][x]), e_border_direction_horizontal);
		tile_set_border_and_update(&(self->tiles[BOARD_BORDER_U + BOARD_HEIGHT][x]), e_border_direction_horizontal);
	}
}

