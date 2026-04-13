# Building and environment related variables
C := gcc
SRC_DIR := src
CFLAGS := -Wall -Werror -Ofast -fPIC -DNDEBUG
DEBUG_CFLAGS := -Wall -Werror -O0 -g -fPIC 
TEST_DIR := tests
LIB := libfireside
TESTS := test_fireside_lib

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
LIB_OBJECTS = $(patsubst $(SRC_DIR)/%.c, %.o, $(SRC_FILES))

LIB_DEBUG_OBJECTS = $(patsubst $(SRC_DIR)/%.c, %_debug.o, $(SRC_FILES))

TEST_SRC_FILES = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJECTS = $(patsubst $(TEST_DIR)/%.c, %.o, $(TEST_SRC_FILES))


.PHONY: all clean

all: $(LIB).so
test: $(TESTS)

%.o: $(SRC_DIR)/%.c
	$(C) $(CFLAGS) -c $< -o $@ -Iinclude

%_debug.o: $(SRC_DIR)/%.c
	$(C) $(DEBUG_CFLAGS) -c $< -o $@ -Iinclude

%.o: $(TEST_DIR)/%.c
	$(C) $(DEBUG_CFLAGS) -Wl,--wrap=malloc -c $< -o $@ -Iinclude -Itest

# Build the shared library
$(LIB).so: $(LIB_OBJECTS)
	$(C) $(CFLAGS) -shared $< -o $@ -Iinclude

# Build the shared library for debug
$(LIB)_debug.so: $(LIB_DEBUG_OBJECTS)
	$(C) $(DEBUG_CFLAGS) -shared $? -o $@ -Iinclude

# Build malloc preload library
test_malloc.so: $(TEST_DIR)/preload/test_malloc.c
	$(C) -shared -fPIC -o test_malloc.so $< -ldl

# Build tests
$(TESTS): $(LIB)_debug.so test_malloc.so $(TEST_OBJECTS)
	$(C) -pie -Wl,-rpath=. -rdynamic $(DEBUG_CFLAGS) $(TEST_OBJECTS) -o $@ -L. -lfireside_debug -Iinclude
	LD_PRELOAD=./test_malloc.so ./$(TESTS)

# Clean up
clean:
	rm -rf *.o *.so $(TESTS)
