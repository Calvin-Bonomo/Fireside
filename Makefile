# Building and environment related variables
C := gcc
SRC_DIR := src
CFLAGS := -Wall -Ofast
TEST_DIR := test
LIB := fireside_lib.so
TESTS := test_fireside_lib

all: $(LIB)
test: $(TESTS)

# Including sub makefiles
include $(SRC_DIR)/Makefile $(TEST_DIR)/Makefile
INCLUDE_DIRS := $(addprefix -I,$(INCLUDE_DIRS))
TEST_INCLUDE_DIRS := $(addprefix -I,$(TEST_INCLUDE_DIRS))

# Build the shared library
$(LIB): $(LIB_OBJECTS)
	$(C) -shared $(CFLAGS) -o $@ $? $(INCLUDE_DIRS)

# Build tests
$(TESTS): $(TEST_OBJECTS) $(LIB)
	$(C) $(TEST_CFLAGS) -o $@ $? $(TEST_INCLUDE_DIRS)

# Clean up
.PHONY: clean
clean:
	rm -rf *.o $(LIB) $(TESTS)