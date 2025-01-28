#ifndef UTILS
#define UTILS

#include "stdio.h"

#define BEGIN_TEST(group_name) unsigned int testsPassed = 0, testsFailed = 0; \
printf("Starting tests in group: %s.\n", group_name);

#define END_TEST(group_name) \
printf("Tests in group, %s, complete.\n%s:    %d tests passed, %d tests failed\n", group_name, group_name, testsPassed, testsFailed);

#define TEST_EQ(test_name, res, expected) \
if (res == expected) { \
  testsPassed++; \
  printf("Passed test %s.\n", test_name); \
} \
else { \
  testsPassed++; \
  printf("Failed test %s.\n", test_name); \
}

#define TEST_NEQ(test_name, res, expected) \
if (res != expected) { \
  testsPassed++; \
  printf("Passed test %s.\n", test_name); \
} \
else { \
  testsPassed++; \
  printf("Failed test %s.\n", test_name); \
} \

#endif