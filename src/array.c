#include "array.h"

#include "stdlib.h"
#include "assert.h"

#include "utils.h"


int array_init(array *arr, uint n, uint s) {
    assert(arr && "arr must not be NULL");
    assert(n && "n must be greater than 0");
    assert(s && "s must be greater than 0");
    clear(arr, sizeof(array));

    if (!(arr->data = malloc(n * s)))
        return 1;
    arr->elementSize = s;
    arr->count = n;

    return 0;
}

void array_free(array *arr) {
    assert(arr && "arr must not be NULL");
    
    free(arr->data);
    clear(arr, sizeof(array));
}

void *array_get(array *arr, uint i) {
    assert(arr && "arr must not be NULL");
    assert(i < arr->count && "i must not be out-of-bounds");

    return ((char *)arr->data) + i * arr->elementSize;
}

void array_set(array *arr, void *val, uint i) {
    assert(arr && "arr must not be null");
    assert(val && "val must not be null");

    copy(val, array_get(arr, i), sizeof(arr->elementSize));
}
