#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "functions.h"

VECTOR_TYPE copy_int(VECTOR_TYPE x) { return x; }
void delete_int(VECTOR_TYPE x) { (void)x; }

int main() {
    Vector v = create_vector(2, copy_int, delete_int);

    push_back_vector(&v, 10);
    push_back_vector(&v, 20);
    assert(v.size == 2);
    assert(get_at_vector(&v, 0) == 10);
    assert(get_at_vector(&v, 1) == 20);

    delete_at_vector(&v, 0);
    assert(v.size == 1);
    assert(get_at_vector(&v, 0) == 20);

    erase_vector(&v);

    printf("All tests passed!\n");
    return 0;
}
