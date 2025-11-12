#include <stdio.h>
#include "functions.h"

int main() {
    Vector v = create_vector(2, copy, delete);

    push_back_vector(&v, 10);
    push_back_vector(&v, 20);

    delete_at_vector(&v, 0);

    for (size_t i = 0; i < v.size; i++) {
        printf("%d ", get_at_vector(&v, i));
    }
    printf("\n");

    erase_vector(&v);
    return 0;
}
