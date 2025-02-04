# Test runner related variables
TEST_RUNNER := test_runner.o
TEST_OBJECTS += $(TEST_RUNNER)

# Array test related variables
ARRAY_DIR := array
ARRAY_TEST_INCLUDE := $(TEST_DIR)/$(ARRAY_DIR)
TEST_INCLUDE_DIRS += $(ARRAY_TEST_INCLUDE)
TEST_SUB_MAKES += $(ARRAY_TEST_INCLUDE)/Makefile

# Test runner target
$(TEST_RUNNER):
	$(C) $(TEST_CFLAGS) -c $(TEST_DIR)/test_runner.c $(TEST_INCLUDE_DIRS)

# Include extra Makefiles
include $(TEST_SUB_MAKES)