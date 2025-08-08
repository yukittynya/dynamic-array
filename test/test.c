#include "../src/darray.h"
#include "../src/arena.h"

#include <stdio.h>

static Arena arena = {0};

int main() {
    DArray arr = darray_new(&arena, int);

    int a = 1;
    int b = 2;
    darray_push(&arr, int, a);
    darray_push(&arr, int, b);
    
    for (int i = 0; i < arr.count; i++) {
        printf("%d\n", *(int*) darray_get(&arr, i));
    }

    arena_free(&arena);
}
