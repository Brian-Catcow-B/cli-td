#include "data_structures.h"
#include <stdlib.h>
#include "log.h"

#define BASE_VECTOR_ALLOCATED_SIZE 15

struct vector_t {
	void **data;
	size_t size;
	size_t allocated_size;
};

vector_t *alloc_init_vector() {
	vector_t *new_vec = malloc(sizeof(vector_t));
	new_vec->data = malloc(sizeof(void *) * BASE_VECTOR_ALLOCATED_SIZE);
	new_vec->size = 0;
	new_vec->allocated_size = BASE_VECTOR_ALLOCATED_SIZE;

	LOG_VA("new_vec pointer: %lx\n", (size_t) new_vec);
	return new_vec;
}

void dealloc_deinit_vector(vector_t *self) {
	free(self->data);
	free(self);
}

void vector_push_back(vector_t *self, void *elem) {
	LOG_VA("vector_push_back: %lx\n", (size_t) elem);
	if (self->size == self->allocated_size) {
		LOG_VA("calling realloc; self->size == self->allocated_size == %lu\n", self->size);
		LOG_VA("realloc(self->data, %lu);\n", sizeof(void *) * (self->allocated_size + BASE_VECTOR_ALLOCATED_SIZE));
		self->data = realloc(self->data, sizeof(void *) * (self->allocated_size + BASE_VECTOR_ALLOCATED_SIZE));
	}

	self->data[self->size] = elem;
	self->size++;
}

void vector_insert_index(vector_t *self, size_t index, void *elem) {
	if (self->size == 0) {
		vector_push_back(self, elem);
	} else {
		vector_push_back(self, self->data[self->size - 1]);
		for (size_t i = self->size - 1; i > index; i--) {
			self->data[i] = self->data[i - 1];
		}
		self->data[index] = elem;
		self->size++;
	}
}

size_t vector_size(vector_t *self) {
	return self->size;
}

void *vector_remove_index(vector_t *self, size_t index) {
	void *retval = self->data[index];

	for (size_t i = index; i + 1 < self->size; i++) {
		self->data[i] = self->data[i + 1];
	}

	return retval;
}

void *vector_at(vector_t *self, size_t index) {
	return self->data[index];
}

