#ifndef _TEST_UTIL_H_
#define _TEST_UTIL_H_

#include "stdio.h"

unsigned int tests_run = 0, tests_passed = 0;

int malloc_should_fail = 0;


// Checks if `cond` is true
#define TEST(cond, msg) do {                      \
    ++tests_run;                                  \
    if (cond)                                     \
        ++tests_passed;                           \
    else                                          \
        fprintf(                                  \
            stderr,                               \
            "In %s:%s@%d.\nTest %d failed: %s\n", \
            __func__,                             \
            __FILE__,                             \
            __LINE__,                             \
            tests_run,                            \
            msg                                   \
        );                                        \
} while(0);

// Checks if `val == exp`
// Note: `val == exp` must be a valid C statement
#define TEST_EQ(val, exp, msg) do {               \
    ++tests_run;                                  \
    if (val == exp)                               \
        ++tests_passed;                           \
    else                                          \
        fprintf(                                  \
            stderr,                               \
            "In %s:%s@%d.\nTest %d failed: %s\n", \
            __func__,                             \
            __FILE__,                             \
            __LINE__,                             \
            tests_run,                            \
            msg                                   \
        );                                        \
} while(0);

#define TEST_MALLOC_FAIL(val, exp, msg) do {      \
    ++tests_run;                                  \
    malloc_should_fail = 1;                       \
    __typeof__(val) res = (val);                  \
    malloc_should_fail = 0;                       \
    if (res == exp)                               \
        ++tests_passed;                           \
    else                                          \
        fprintf(                                  \
            stderr,                               \
            "In %s:%s@%d.\nTest %d failed: %s\n", \
            __func__,                             \
            __FILE__,                             \
            __LINE__,                             \
            tests_run,                            \
            msg                                   \
        );                                        \
} while(0);

#define END_TESTS fprintf(stderr, "\n===== %d/%d Tests Passed =====\n", tests_passed, tests_run);

#endif
