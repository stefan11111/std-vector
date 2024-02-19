#include <stdlib.h>
#include <string.h>

typedef struct{
    char *elements;
    void (*constructor)();
    void (*destructor)();
    void (*copy)();
    void* (*reallocator)();
    int size;
    int total_size;
} vec_t;

static inline void handle_error()
{
    exit(0);
}

void init_vector(vec_t *ptr, int size, int num_elements, void (*constructor)(), void (*destructor)(), void (*copy)(), void* (*reallocator)())
{

    ptr->constructor = constructor;

    ptr->destructor = destructor;

    ptr->copy = copy;

    ptr->reallocator = reallocator;

    ptr->elements = malloc(num_elements * size);

    ptr->total_size = num_elements;

    ptr->size = size;

    if(ptr->elements == NULL) {
        handle_error();
    }

    for(char *it = ptr->elements; it < ptr->elements + num_elements * size; it += size) {
        ptr->constructor(it, size);
    }
}

void resize_vector(vec_t *ptr, int num_elements)
{
    int size = ptr->size;

    void *tmp = ptr->reallocator(ptr->elements, num_elements * size);

    if(tmp == NULL) {
        handle_error();
    }

    ptr->elements = tmp;

    if(num_elements > ptr->total_size) {
        for(char *it = ptr->elements + (ptr->total_size) * size; it < ptr->elements + num_elements * size; it += size) {
            ptr->constructor(it, size);
        }

        ptr->total_size = num_elements;
        return;
    }

    for(char *it = ptr->elements + (ptr->total_size - 1) * size; it >= ptr->elements + num_elements * size ; it -= size) {
        ptr->destructor(it);
    }

    ptr->total_size = num_elements;
}

void free_vector(vec_t *ptr)
{
    resize_vector(ptr, 0);
}

void write_element(vec_t *ptr, int pos, void *data, int size)
{
    if(size > ptr->size) {
        size = ptr->size;
    }
    ptr->copy(ptr->elements + pos * ptr->size, data, size);
}

void read_element(vec_t *ptr, int pos, void *data, int size)
{
    if(size > ptr->size) {
        size = ptr->size;
    }
    ptr->copy(data, ptr->elements + pos * ptr->size, size);
}

static inline void nop()
{
}

int main()
{
    int size = 1;
    int n = 1000000000;
    vec_t vec;

    char *str="very long string, longer that 8 char's";

    char dest[100];

    volatile char *p = dest;

    init_vector(&vec, size, n, &nop, &nop, &memcpy, &realloc);
    for(int i = 0; i < n; i++) {
        write_element(&vec, i, str, size);
    }

    n = 20;

    resize_vector(&vec, n);

    for(int i = 0; i < n; i++) {
        write_element(&vec, i, str, size);
    }

    for(int i = 0; i < n; i++) {
        read_element(&vec, i, p, size);
//        printf("%s\n", p);
    }

    return 0;
}

