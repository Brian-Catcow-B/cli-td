#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <stddef.h>

typedef struct vector_t vector_t;
vector_t *alloc_init_vector();
void dealloc_deinit_vector(vector_t *self);
void vector_push_back(vector_t *self, void *elem);
void vector_insert_index(vector_t *self, size_t index, void *elem);
size_t vector_size(vector_t *self);
void *vector_remove_index(vector_t *self, size_t index);
void *vector_at(vector_t *self, size_t index);

#endif // DATA_STRUCTURES_H

