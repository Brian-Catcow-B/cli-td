#ifndef POS2D_H
#define POS2D_H

#include <stddef.h>

typedef struct pos2d_t {
	int y;
	int x;
} pos2d_t;

pos2d_t pos2d(int y, int x);

typedef enum e_relative_pos {
	e_relative_pos_U,
	e_relative_pos_UR,
	e_relative_pos_R,
	e_relative_pos_DR,
	e_relative_pos_D,
	e_relative_pos_DL,
	e_relative_pos_L,
	e_relative_pos_UL,
} e_relative_pos;

char linechar_from_relative_pos(e_relative_pos relative_pos);

typedef struct pos2d_vec_t {
	pos2d_t *data;
	size_t size;
	size_t _allocated_size;
} pos2d_vec_t;

void init_pos2d_vec(pos2d_vec_t *self, size_t initial_allocated_size);
void pos2d_vec_push_back(pos2d_vec_t *self, pos2d_t pos) {
void deinit_pos2d_vec(pos2d_vec_t *self);

#endif // POS2D_H

