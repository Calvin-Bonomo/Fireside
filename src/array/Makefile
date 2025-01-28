# Array related variables
ARRAY_OBJECT := array.o
LIB_OBJECTS += $(ARRAY_OBJECT)

# Array build target
$(ARRAY_OBJECT):
	$(C) $(CFLAGS) -c $(ARRAY_INCLUDE)/array.c
	cp $(ARRAY_INCLUDE)/array.h include/array.h