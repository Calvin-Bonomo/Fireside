# Array related variables
ARRAY_DIR := array
ARRAY_INCLUDE := $(SRC_DIR)/$(ARRAY_DIR)
INCLUDE_DIRS += $(ARRAY_DIR)
LIB_SUB_MAKES += $(ARRAY_INCLUDE)/Makefile

# List related variables
LIST_DIR := list
LIST_INCLUDE := $(SRC_DIR)/$(LIST_DIR)
INCLUDE_DIRS += $(LIST_DIR)
LIB_SUB_MAKES += $(LIST_INCLUDE)/Makefile

HEAP_DIR := heap
HEAP_INCLUDE := $(SRC_DIR)/$(HEAP_DIR)
INCLUDE_DIRS += $(HEAP_DIR)
LIB_SUB_MAKES += $(HEAP_INCLUDE)/Makefile

# Include all extra Makefiles
include $(LIB_SUB_MAKES)