#include <stdlib.h>
#include <string.h>

typedef struct{
    void **elements;
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

void init_vector(vec_t *ptr, int size, int num_elements)
{
    ptr->elements = malloc(num_elements * sizeof(void*));

    ptr->total_size = num_elements;

    ptr->size = size;

    if(ptr->elements == NULL) {
        handle_error();
    }

    for(void **it = ptr->elements; it < ptr->elements + num_elements; it++) {
        init_element(it, size);
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
            init_element(it, size);
        }

        ptr->total_size = num_elements;
        return;
    }

    for(void **it = ptr->elements + ptr->total_size - 1; it >= ptr->elements + num_elements ; it--) {
        free_element(it);
    }

    ptr->total_size = num_elements;
}

void free_vector(vec_t *ptr)
{
    resize_vector(ptr, 0);
}

void write_element(vec_t *ptr, int pos, void *data)
{
    memcpy(ptr->elements[pos], data, ptr->size);
}

void read_element(vec_t *ptr, int pos, void *data)
{
    memcpy(data, ptr->elements[pos], ptr->size);
}

int main()
{
    int size = 8;
    int n = 10;
    vec_t vec;

    char *str="very long string, longer that 8 char's";

    char dest[100];

    init_vector(&vec, size, n);
    for(int i = 0; i < n; i++) {
        write_element(&vec, i, str);
    }

    resize_vector(&vec, 20);

    n = 20;

    for(int i = 0; i < n; i++) {
        write_element(&vec, i, str);
    }


    for(int i = 0; i < n; i++) {
        read_element(&vec, i, dest);
        printf("%s\n", dest);
    }
    return 0;
}

