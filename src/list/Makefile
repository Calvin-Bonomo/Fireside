# List related variables
LIST_OBJECT := list
LIB_OBJECTS += $(LIST_OBJECT).o
LIB_DEBUG_OBJECTS += $(LIST_OBJECT)_debug.o

# List build target
$(LIST_OBJECT).o:
	$(C) $(CFLAGS) -o $@ -c $(LIST_INCLUDE)/list.c $(PRIVATE_INCLUDE_DIRS)
	cp $(LIST_INCLUDE)/list.h include/list.h

# List_debug build target
$(LIST_OBJECT)_debug.o:
	$(C) $(DEBUG_CFLAGS) -o $@ -c $(LIST_INCLUDE)/list.c $(PRIVATE_INCLUDE_DIRS)
	cp $(LIST_INCLUDE)/list.h include/list.h