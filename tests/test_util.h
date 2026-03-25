#ifndef _TEST_UTIL_H_
#define _TEST_UTIL_H_

#include "stdio.h"

unsigned long long tests_run = 0, tests_passed = 0;

// Checks if `cond` is true
#define TEST(cond, msg) (                    \
  ++tests_run;                               \
  if (cond)                                  \
    ++tests_passed;                          \
  else                                       \
    fprintf(                                 \
      stderr,                                \
      "In %s:%s@%d.\nTest %d failed: %s\n ", \
      __func__,                              \
      __FILE__,                              \
      __LINE__,                              \
      tests_run,                             \
      msg                                    \
    );                                       \
  )

// Checks if `val == exp`
// Note: `val == exp` must be a valid C statement
#define TEST_EQ(val, exp, msg) (             \
  ++tests_run;                               \
  if (val == exp)                            \
    ++tests_passed;                          \
  else                                       \
    fprintf(                                 \
      stderr,                                \
      "In %s:%s@%d.\nTest %d failed: %s\n ", \
      __func__,                              \
      __FILE__,                              \
      __LINE__,                              \
      tests_run,                             \
      msg                                    \
    );                                       \
  )

#define END_TESTS ( fprintf(stderr, "\n===== %d/%d Tests Passed =====\n", tests_passed, tests_run); )

#endif