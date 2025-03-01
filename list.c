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

    if (num_elements == ptr->total_size) {
        return;
    }

    if (ptr->overallocate && num_elements > ptr->total_size
                          && num_elements < (ptr->total_size << 1)) {
        num_elements = ptr->total_size;
    }

    char *tmp = malloc(num_elements * size);

    char *it_2 = tmp;

    if(tmp == NULL) {
        ptr->malloc_error();
    }

    size_t min_size = ptr->total_size < num_elements ? ptr->total_size : num_elements;

    for(char *it = ptr->elements; it < ptr->elements + min_size * size; it += size) {
        ptr->move(it_2, it, size);
        it_2 += size;
    }

    char *free_p = ptr->elements;

    ptr->elements = tmp;


    /* if new_size > old_size */
    for(char *it = ptr->elements + (ptr->total_size) * size; it < ptr->elements + num_elements * size; it += size) {
        ptr->constructor(it);
    }


    /* if new_size < old size */
    for(char *it = free_p + (ptr->total_size - 1) * size; it >= free_p + num_elements * size ; it -= size) {
        ptr->destructor(it);
    }

    free(free_p);

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
