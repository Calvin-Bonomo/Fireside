# Test runner related variables
TEST_RUNNER := test_runner.o
TEST_OBJECTS += $(TEST_RUNNER)

# Array test related variables
ARRAY_DIR := array
ARRAY_TEST_INCLUDE := $(TEST_DIR)/$(ARRAY_DIR)
TEST_INCLUDE_DIRS += $(ARRAY_TEST_INCLUDE)
TEST_SUB_MAKES += $(ARRAY_TEST_INCLUDE)/Makefile

# Array test related variables
LIST_DIR := list
LIST_TEST_INCLUDE := $(TEST_DIR)/$(LIST_DIR)
TEST_INCLUDE_DIRS += $(LIST_TEST_INCLUDE)
TEST_SUB_MAKES += $(LIST_TEST_INCLUDE)/Makefile

# Heap test related variables
HEAP_DIR := heap
HEAP_TEST_INCLUDE := $(TEST_DIR)/$(HEAP_DIR)
TEST_INCLUDE_DIRS += $(HEAP_TEST_INCLUDE)
TEST_SUB_MAKES += $(HEAP_TEST_INCLUDE)/Makefile

# Test runner target
$(TEST_RUNNER):
	$(C) $(TEST_CFLAGS) -c $(TEST_DIR)/test_runner.c $(TEST_INCLUDE_DIRS)

# Include extra Makefiles
include $(TEST_SUB_MAKES)