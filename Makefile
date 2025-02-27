# Building and environment related variables
C := gcc
SRC_DIR := src
CFLAGS := -Wall -Werror -Ofast
TEST_DIR := test
LIB := libfireside
TESTS := test_fireside_lib
TEST_INCLUDE_DIRS := include

.PHONY: $(LIB).so $(LIB_OBJECTS) $(TESTS) $(TEST_OBJECTS) clean
all: $(LIB).so
test: $(TESTS)

# Including sub makefiles
include $(SRC_DIR)/Makefile $(TEST_DIR)/Makefile
ARG_INCLUDE_DIRS := $(addprefix -I$(SRC_DIR)/,$(INCLUDE_DIRS))
TEST_INCLUDE_DIRS := $(addprefix -I,$(TEST_INCLUDE_DIRS))

# Build the shared library
$(LIB).so: $(LIB_OBJECTS)
	$(C) -shared $(CFLAGS) $? -o $@ $(ARG_INCLUDE_DIRS)

# Build tests
$(TESTS): $(LIB).so $(TEST_OBJECTS)
	mkdir -p include
	$(C) -pie -Wl,-rpath=. $(TEST_CFLAGS) $(TEST_OBJECTS) -o $@ -L. -lfireside -Iinclude/ $(TEST_INCLUDE_DIRS)
	./$(TESTS)

# Clean up
clean:
	rm -rf *.o *.so $(TESTS) ./include/*