#ifndef TEST_ARRAY_H
#define TEST_ARRAY_H

#include "array.h"

#include "test_utils.h"

#define TEST_ARRAY_SIZE 100

void test_array()
{
    array arr;

    TEST_MALLOC_FAIL(array_init(&arr, TEST_ARRAY_SIZE, sizeof(int)), 1, "array init fail");
}

#endif
