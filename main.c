#include <stdio.h>
#include <stdlib.h>

#define VECTOR_TYPE int


typedef struct {
    VECTOR_TYPE *data;
    size_t size;
    size_t capacity;
    VECTOR_TYPE (*CopyVoidPtr)(VECTOR_TYPE);
    void (*DeleteVoidPtr)(VECTOR_TYPE);
} Vector;

Vector create_vector(size_t initial_capacity,
                     VECTOR_TYPE (*CopyFunc)(VECTOR_TYPE),
                     void (*DeleteFunc)(VECTOR_TYPE)) {
    Vector v;
    v.size = 0;
    v.capacity = initial_capacity;
    v.CopyVoidPtr = CopyFunc;
    v.DeleteVoidPtr = DeleteFunc;
    v.data = malloc(initial_capacity * sizeof(VECTOR_TYPE));
    return v;
}

VECTOR_TYPE copy_int(VECTOR_TYPE x) { return x; }
void delete_int(VECTOR_TYPE x) { (void)x; }

int main() {
    Vector v = create_vector(5, copy_int, delete_int);

    printf("Vector создан. Размер: %zu, Вместимость: %zu\n", v.size, v.capacity);
    free(v.data);

    return 0;
}
