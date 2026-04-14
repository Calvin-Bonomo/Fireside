#ifndef TEST_ARRAY_H
#define TEST_ARRAY_H

#include "array.h"

#include "test_utils.h"

#define TEST_ARRAY_SIZE 100

void test_array()
{
    array arr;
    
    // Test array_init
    TEST_MALLOC_FAIL(array_init(&arr, TEST_ARRAY_SIZE, sizeof(int)), 1, "array init fail");

    TEST_EQ(array_init(&arr, TEST_ARRAY_SIZE, sizeof(int)), 0, "array init success");

    // Test array set
    for (uint i = 0; i < TEST_ARRAY_SIZE; i++)
        array_set(&arr, &i, i);

    for (uint i = 0; i < TEST_ARRAY_SIZE; i++)
        TEST_EQ(((int *)arr.data)[i], i, "array get");

    // Test array get
    for (uint i = 0; i < TEST_ARRAY_SIZE; i++)
        TEST_EQ(*(int *)array_get(&arr, i), (int)i, "array set");

    array_free(&arr);
}

#endif
