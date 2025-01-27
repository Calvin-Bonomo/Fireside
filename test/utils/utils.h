#ifndef UTILS
#define UTILS

typedef struct {
  char *testGroupName;
  unsigned char testNameSize;
  unsigned int numTestsPassed;
  unsigned int numTestsFailed;
} test_data_t;

typedef int test_runner(test_data_t *data);

int init_test_data(test_data_t *data, char* testGroupName, int nameSize);
int free_test_data(test_data_t *data);

#endif