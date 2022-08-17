#include "pos2d.h"

pos2d_t pos2d(int y, int x) {
	pos2d_t p;
	p.y = y;
	p.x = x;
	return p;
}

char linechar_from_relative_pos(e_relative_pos relative_pos) {
	switch (relative_pos) {
		case e_relative_pos_U:
		case e_relative_pos_D:
			return '|';
		case e_relative_pos_L:
		case e_relative_pos_R:
			return '-';
		case e_relative_pos_UL:
		case e_relative_pos_DR:
			return '\\';
		case e_relative_pos_DL:
		case e_relative_pos_UR:
			return '/';
		default:
			return '?';
	}
}

void priv_pos2d_vec_increase_alloc_size(pos2d_vec_t *self);

void init_pos2d_vec(pos2d_vec_t *self, size_t initial_allocated_size) {
	self->data = malloc(sizeof(pos2d_vec_t) * initial_allocated_size);
	self->size = 0;
	self->_allocated_size = initial_allocated_size;
}

void priv_pos2d_vec_increase_alloc_size(pos2d_vec_t *self) {
	self->data = realloc(self->data, sizeof(pos2d_vec_t) * (self->_allocated_size + 15));
	self->_allocated_size += 15;
}

void pos2d_vec_push_back(pos2d_vec_t *self, pos2d_t pos) {
	if (self->size == self->_allocated_size)
		priv_pos2d_vec_increase_alloc_size(self);
	self->data[self->size] = pos;
	self->size++;
}

void deinit_pos2d_vec(pos2d_vec_t *self) {
	free(self->data);
}

