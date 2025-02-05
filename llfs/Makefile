## Blueprint Makefile
SRC_FILES := test list
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

## create vars for target, src and object files
EXE := $(BIN_DIR)/a.out
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC_FILES)))

INCLUDE := -Isrc

## for debugging
CFLAGS := -fsanitize=address -fsanitize=undefined -Wall -Wextra -g -MMD -MP $(INCLUDE)
LDFLAGS := -fsanitize=address -fsanitize=undefined $(INCLUDE)

## for normal comp
# CFLAGS := -Wall -Wextra -g -MMD -MP
# LDFLAGS :=

## select compiler
# CC := gcc-14
CC := clang


## Targets
# Phony targets aren't treated as files
.PHONY: all run clean

# Default target, executed with 'make' command
build: $(EXE)

# Execute immediatelly after building
run: $(EXE)
	./bin/a.out

# Link all the objectfiles into an exe
$(EXE): $(OBJ) | $(BIN_DIR) # 
	$(CC) $(LDFLAGS) $^ -o $@
	dsymutil $@

# Only source files that have been changed get rebuilt
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean for rebuilt - Using implicit variable RM (rm -f)
clean:
	@$(RM) -r $(OBJ_DIR) $(BIN_DIR)

# Make sure directories exist
$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

# check header files for changes
-include $(OBJ:.o=.d)



### Helper Legend ###
# normal-prerequisites | order-only-prerequisites (no out of date check)

### Automatic variables:
# $^: all prerequisites
# $<: first prerequisite
# $@: target

### Specifics
# -MDD, -MP: create .d files for header deps
# -g: additional debug info gets created
# dsymutil: extract debug info into seperate file, Mac thing I think..
