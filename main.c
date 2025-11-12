#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VECTOR_TYPE int

typedef struct {
    VECTOR_TYPE *data;
    size_t size;
    size_t capacity;
    VECTOR_TYPE (*CopyVoidPtr)(VECTOR_TYPE);
    void (*DeleteVoidPtr)(VECTOR_TYPE);
} Vector;

Vector create_vector(size_t initial_capacity, VECTOR_TYPE (*CopyFunc)(VECTOR_TYPE), void (*DeleteFunc)(VECTOR_TYPE)) {
    Vector v;
    v.size = 0;
    v.capacity = initial_capacity;
    v.CopyVoidPtr = CopyFunc;
    v.DeleteVoidPtr = DeleteFunc;
    v.data = malloc(initial_capacity * sizeof(VECTOR_TYPE));
    return v;
}

void erase_vector(Vector *v) {
    if (!v) return;
    if (v->data) {
        if (v->DeleteVoidPtr) {
            for (size_t i = 0; i < v->size; i++)
                v->DeleteVoidPtr(v->data[i]);
        }
        free(v->data);
    }
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

int is_equal_vector(const Vector *v1, const Vector *v2) {
    if (!v1 || !v2) {
        return 0;
    }
    if (v1->size != v2->size) {
        return 0;
    }
    for (size_t i = 0; i < v1->size; i++) {
        if (v1->data[i] != v2->data[i])
            return 0;
    }
    return 1;
}

void copy_vector(Vector *dest, const Vector *src) {
    if (!dest || !src) {
        return;
    }
    if (dest->DeleteVoidPtr) {
        for (size_t i = 0; i < dest->size; i++)
            dest->DeleteVoidPtr(dest->data[i]);
    }
    free(dest->data);
    dest->size = src->size;
    dest->capacity = src->capacity;
    dest->CopyVoidPtr = src->CopyVoidPtr;
    dest->DeleteVoidPtr = src->DeleteVoidPtr;
    dest->data = malloc(dest->capacity * sizeof(VECTOR_TYPE));
    for (size_t i = 0; i < dest->size; i++) {
        if (dest->CopyVoidPtr) {
            dest->data[i] = dest->CopyVoidPtr(src->data[i]);
        } else {
            dest->data[i] = src->data[i];
        }
    }
}

Vector *copy_vector_new(const Vector *src) {
    if (!src) {
        return NULL;
    }
    Vector *new_v = malloc(sizeof(Vector));
    if (!new_v) {
        return NULL;
    }
    new_v->size = src->size;
    new_v->capacity = src->capacity;
    new_v->CopyVoidPtr = src->CopyVoidPtr;
    new_v->DeleteVoidPtr = src->DeleteVoidPtr;
    new_v->data = malloc(new_v->capacity * sizeof(VECTOR_TYPE));
    if (!new_v->data) {
        free(new_v);
        return NULL;
    }
    for (size_t i = 0; i < new_v->size; i++) {
        if (new_v->CopyVoidPtr)
            new_v->data[i] = new_v->CopyVoidPtr(src->data[i]);
        else
            new_v->data[i] = src->data[i];
    }
    return new_v;
}

void push_back_vector(Vector *v, VECTOR_TYPE value) {
    if (!v) {
        return;
    }
    if (v->size == v->capacity) {
        size_t new_capacity;
        if (v->capacity > 0) {
            new_capacity = v->capacity + 1;
        } else {
            new_capacity = 1;
        }
        VECTOR_TYPE *new_data = realloc(v->data, new_capacity * sizeof(VECTOR_TYPE));
        if (!new_data) {
            return;
        }
        v->data = new_data;
        v->capacity = new_capacity;
    }
    if (v->CopyVoidPtr) {
        v->data[v->size] = v->CopyVoidPtr(value);
    } else {
        v->data[v->size] = value;
    }
    v->size++;
}

void delete_at_vector(Vector *v, size_t index) {
    if (!v || index >= v->size) {
        return;
    }
    if (v->DeleteVoidPtr) {
        v->DeleteVoidPtr(v->data[index]);
    }
    for (size_t i = index; i < v->size - 1; i++) {
        v->data[i] = v->data[i + 1];
    }
    v->size--;
}

VECTOR_TYPE get_at_vector(const Vector *v, size_t index) {
    if (!v || index >= v->size) {
        return (VECTOR_TYPE)0;
    }
    return v->data[index];
}

void delete_vector(Vector *v) {
    if (!v) {
        return;
    }
    if (v->DeleteVoidPtr) {
        for (size_t i = 0; i < v->size; i++)
            v->DeleteVoidPtr(v->data[i]);
    }
    free(v->data);
    free(v);
}

VECTOR_TYPE copy(VECTOR_TYPE x) { return x; }
void delete(VECTOR_TYPE x) { (void)x; }

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
