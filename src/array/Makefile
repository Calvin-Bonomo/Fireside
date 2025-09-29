# Array related variables
ARRAY_OBJECT := array
LIB_OBJECTS += $(ARRAY_OBJECT).o
LIB_DEBUG_OBJECTS += $(ARRAY_OBJECT)_debug.o

# Array build target
$(ARRAY_OBJECT).o:
	$(C) $(CFLAGS) -o $@ -c $(ARRAY_INCLUDE)/array.c $(PRIVATE_INCLUDE_DIRS)
	cp $(ARRAY_INCLUDE)/array.h include/array.h

# Array_debug build target
$(ARRAY_OBJECT)_debug.o:
	$(C) $(DEBUG_CFLAGS) -o $@ -c $(ARRAY_INCLUDE)/array.c $(PRIVATE_INCLUDE_DIRS)
	cp $(ARRAY_INCLUDE)/array.h include/array.h