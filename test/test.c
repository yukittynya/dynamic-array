#include "../src/darray.h"
#include "../src/arena.h"

static Arena arena = {0};

int main() {
    DArray arr = darray_new(&arena, int);

}
