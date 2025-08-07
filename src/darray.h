#ifndef DARRY_H
#define DARRY_H

#include <stddef.h>

#define USING_ARENA
#include "arena.h"

#define ARRAY_DEFAULT_CAPACITY 8

typedef struct {
    void* items;
    size_t count;
    size_t capacity;
    Arena* arena; 
} DArray;

static inline DArray _darray_new_impl(Arena* arena, size_t element_size, size_t capacity) {
    return (DArray) {
        .items = capacity > 0 ? arena_alloc(arena, element_size * capacity) : NULL,
        .count = 0,
        .capacity = capacity,
        .arena = arena,
    };
}

#define darray_new(arena, type) \
    _darray_new_impl(arena, sizeof(type), ARRAY_DEFAULT_CAPACITY)

#define darray_new_with_capacity(arena, type, cap) \
    _darray_new_impl(arena, sizeof(type), cap)

#define darray_new_empty(arena, type) \
    _darray_new_impl(arena, sizeof(type), 0)

#endif // !DARRY_H
