# Heap related variables
HEAP_OBJECT := heap
LIB_OBJECTS += $(HEAP_OBJECT).o
LIB_DEBUG_OBJECTS += $(HEAP_OBJECT)_debug.o

# Heap build target
$(HEAP_OBJECT).o:
	$(C) $(CFLAGS) -o $@ -c $(HEAP_INCLUDE)/heap.c $(PRIVATE_INCLUDE_DIRS)
	cp $(HEAP_INCLUDE)/heap.h include/heap.h

# Heap_debug build target
$(HEAP_OBJECT)_debug.o:
	$(C) $(DEBUG_CFLAGS) -o $@ -c $(HEAP_INCLUDE)/heap.c $(PRIVATE_INCLUDE_DIRS)
	cp $(HEAP_INCLUDE)/heap.h include/heap.h