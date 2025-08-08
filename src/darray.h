#ifndef DARRY_H
#define DARRY_H

#include <assert.h>
#include <stddef.h>

#define USING_ARENA
#include "arena.h"

#define ARRAY_DEFAULT_CAPACITY 8

typedef struct {
    void* items;
    size_t count;
    size_t capacity;
    size_t element_size;
    Arena* arena; 
} DArray;

static inline DArray _darray_new_impl(Arena* arena, size_t element_size, size_t capacity) {
    return (DArray) {
        .items = capacity > 0 ? arena_alloc(arena, element_size * capacity) : NULL,
        .count = 0,
        .capacity = capacity,
        .element_size = element_size,
        .arena = arena,
    };
}

#define darray_new(arena, type) \
    _darray_new_impl(arena, sizeof(type), ARRAY_DEFAULT_CAPACITY)

#define darray_new_with_capacity(arena, type, cap) \
    _darray_new_impl(arena, sizeof(type), cap)

#define darray_new_empty(arena, type) \
    _darray_new_impl(arena, sizeof(type), 0)

static inline void _darray_push(DArray* da, size_t size, void* item) {
    assert(da->element_size == size);

    if (da -> count >= da -> capacity) {
        size_t old_size = da -> capacity * da -> element_size;
        size_t new_size = (da -> capacity ? da -> capacity * 2 : 4) * da -> element_size;

        da -> items = arena_realloc(da -> arena, da -> items, old_size, new_size);
        da -> capacity = (da -> capacity ? da -> capacity * 2 : 4);
    }

    arena_memcpy((char*)da -> items + (size * da -> count), item, size);
    da -> count++;
}

#define darray_push(da, type, item) \
    _darray_push(da, sizeof(type), &(item))

static inline void* _darray_get(DArray* da, size_t index) {
    if (index >= da -> count) return NULL;
    return (void*) ((char*) da -> items + (index * da -> element_size));
}

#define darray_get(da, index) \
    _darray_get(da, index)
 
#endif // !DARRY_H
