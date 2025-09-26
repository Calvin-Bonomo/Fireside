# Replace related variables
HEAP_OBJECT := heap.o
LIB_OBJECTS += $(HEAP_OBJECT)

# Replace build target
$(HEAP_OBJECT):
	$(C) $(CFLAGS) -c $(HEAP_INCLUDE)/heap.c $(PRIVATE_INCLUDE_DIRS)
	cp $(HEAP_INCLUDE)/heap.h include/heap.h