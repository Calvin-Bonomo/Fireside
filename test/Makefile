# Test runner related variables
TEST_RUNNER := test_runner.o
TEST_OBJECTS += $(TEST_RUNNER)

# Test utilities related variables
UTILS_INCLUDE := $(TEST_DIR)/utils
TEST_INCLUDE_DIRS += $(UTILS_INCLUDE)
TEST_SUB_MAKES += $(UTILS_INCLUDE)/Makefile

# Test runner target
$(TEST_RUNNER):
	$(C) $(TEST_CFLAGS) -c $(TEST_DIR)/test_runner.c $(TEST_INCLUDE_DIRS)

# Include extra Makefiles
include $(TEST_SUB_MAKES)