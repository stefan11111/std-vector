#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

void init_vector(vec_t *ptr, size_t size, size_t num_elements, void (*_init_vector)(vec_t *ptr))
{

    (*_init_vector)(ptr);

    ptr->elements = malloc(num_elements * size);

    ptr->total_size = num_elements;

    ptr->size = size;

    if(ptr->elements == NULL) {
        ptr->malloc_error();
    }

    for(char *it = ptr->elements; it < ptr->elements + num_elements * size; it += size) {
        ptr->constructor(it);
    }
}

void resize_vector(vec_t *ptr, size_t num_elements)
{
    size_t size = ptr->size;

    char *tmp = malloc(num_elements * size);

    char *it_2 = tmp;

    if(tmp == NULL) {
        ptr->malloc_error();
    }

    size_t n_size = ptr->total_size < num_elements ? ptr->total_size : num_elements;

    for(char *it = ptr->elements; it < ptr->elements + n_size * size; it += size) {
        ptr->move(it_2, it, size);
        it_2 += size;
    }

    void *free_p = ptr->elements;

    ptr->elements = tmp;

    free(free_p);

    if(num_elements > ptr->total_size) {
        for(char *it = ptr->elements + (ptr->total_size) * size; it < ptr->elements + num_elements * size; it += size) {
            ptr->constructor(it);
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

void write_element(vec_t *ptr, size_t pos, void *data, size_t size)
{
    if(size > ptr->size) {
        size = ptr->size;
    }
    ptr->copy(ptr->elements + pos * ptr->size, data, size);
}

void read_element(vec_t *ptr, size_t pos, void *data, size_t size)
{
    if(size > ptr->size) {
        size = ptr->size;
    }
    ptr->copy(data, ptr->elements + pos * ptr->size, size);
}