# Array related variables
LIST_OBJECT := list.o
LIB_OBJECTS += $(LIST_OBJECT)

# Array build target
$(LIST_OBJECT):
	$(C) $(CFLAGS) -c $(LIST_INCLUDE)/list.c $(PRIVATE_INCLUDE_DIRS)
	cp $(LIST_INCLUDE)/list.h include/list.h