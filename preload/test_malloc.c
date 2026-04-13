#define _GNU_SOURCE

#include "dlfcn.h"
#include "stddef.h"

#include "test_malloc.h"

void *malloc(size_t size) {
    if (malloc_should_fail)
        return NULL;
    static void *(*real_malloc)(size_t) = NULL;
    if (!real_malloc)
        real_malloc = dlsym(RTLD_NEXT, "malloc");
    return real_malloc(size);
}
