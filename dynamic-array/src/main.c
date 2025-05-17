#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define INIT_SIZE 4

typedef struct {
    int *val;
    size_t count;
    size_t capacity;
} arr_t;

void arr_print(arr_t da);
void arr_alloc(arr_t *da, size_t size);
void arr_realloc(arr_t *da);
void arr_free(arr_t *da);

int main(void) {
    arr_t da = {0};
    arr_alloc(&da, INIT_SIZE);
    
    for (size_t i = 0; i < INIT_SIZE*2; ++i) {
        if (da.count >= da.capacity) {
            arr_realloc(&da);
        }
        da.val[i] = i+1;
        da.count += 1;
    }

    arr_print(da);
    arr_free(&da);

    return 0;
}

void arr_print(arr_t da) {
    for (size_t i = 0; i < da.count; ++i) {
        printf("%d->", da.val[i]);
    }
    printf("\n");
}

void arr_alloc(arr_t *da, size_t size) {
    printf("INFO: allocating dynamic array\n");
    da->val = malloc(sizeof(*(da->val))*size);
    assert(da->val != NULL);
    da->count = 0;
    da->capacity = size;
}

void arr_realloc(arr_t *da) {
    printf("INFO: resizing dynamic array\n");
    realloc(da->val, da->capacity*2);
    assert(da->val != NULL);
    da->capacity *= 2;
}

void arr_free(arr_t *da) {
    printf("INFO: freeing dynamic array\n");
    free(da->val);
    da->count = 0;
    da->capacity = INIT_SIZE;
}
