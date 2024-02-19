#include <stdlib.h>
#include <string.h>

typedef struct{
    void **elements;
    void (*constructor)(void **ptr, int size);
    void (*destructor)(void **ptr);
    void (*copy)(void *dest, void *src, int size);
    int size;
    int total_size;
} vec_t;

static inline void handle_error()
{
    exit(0);
}

static inline void init_element(void **ptr, int size)
{
    *ptr = malloc(size);
    if(*ptr == NULL) {
        handle_error();
    }
}

static inline void free_element(void **ptr)
{
    free(*ptr);
}

void init_vector(vec_t *ptr, int size, int num_elements, void (*constructor)(void **ptr, int size), void (*destructor)(void **ptr), void (*copy)(void *dest, void *src, int size))
{

    ptr->constructor = constructor;

    ptr->destructor = destructor;

    ptr->copy = copy;

    ptr->elements = malloc(num_elements * sizeof(void*));

    ptr->total_size = num_elements;

    ptr->size = size;

    if(ptr->elements == NULL) {
        handle_error();
    }

    for(void **it = ptr->elements; it < ptr->elements + num_elements; it++) {
        ptr->constructor(it, size);
    }
}

void resize_vector(vec_t *ptr, int num_elements)
{
    int size = ptr->size;

    void *tmp = realloc(ptr->elements, num_elements * sizeof(void*));

    if(tmp == NULL) {
        handle_error();
    }

    ptr->elements = tmp;

    if(num_elements > ptr->total_size) {
        for(void **it = ptr->elements + ptr->total_size; it < ptr->elements + num_elements; it++) {
            ptr->constructor(it, size);
        }

        ptr->total_size = num_elements;
        return;
    }

    for(void **it = ptr->elements + ptr->total_size - 1; it >= ptr->elements + num_elements ; it--) {
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
    ptr->copy(ptr->elements[pos], data, size);
}

void read_element(vec_t *ptr, int pos, void *data, int size)
{
    if(size > ptr->size) {
        size = ptr->size;
    }
    ptr->copy(data, ptr->elements[pos], size);
}

int main()
{
    int size = 8;
    int n = 10;
    vec_t vec;

    char *str="very long string, longer that 8 char's";

    char len = strlen(str) + 1;

    char dest[100];

    init_vector(&vec, size, n, &init_element, &free_element, &memcpy);
    for(int i = 0; i < n; i++) {
        write_element(&vec, i, str, len);
    }

    resize_vector(&vec, 20);

    n = 20;

    for(int i = 0; i < n; i++) {
        write_element(&vec, i, str, len);
    }


    for(int i = 0; i < n; i++) {
        read_element(&vec, i, dest, len);
        printf("%s\n", dest);
    }
    return 0;
}

