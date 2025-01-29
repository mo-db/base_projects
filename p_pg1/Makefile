### Project files
SRC_FILES := ex_09

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

# -g = include debug info, -O0/1/2 = optimization
# -MMD -MP to create .d files for header deps
CC := gcc-14
CFLAGS := -Wall -g -MMD -MP
LDFLAGS := 

EXE := $(BIN_DIR)/a.out

# OBJ holds all .o files that are given or *.o if none are given
# strip to make sure that " " are not count
ifneq ($(strip $(SRC_FILES)),)
	OBJ := $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC_FILES)))
else
	SRC := $(wildcard $(SRC_DIR)/*.c)
	OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
endif



### Targets
# Phony targets aren't treated as files
.PHONY: all run clean

# Default target, executed with 'make' command
build: $(EXE)

# Execute immediatelly after building
run: $(EXE)
	./bin/a.out

# Main executable target for the project
$(EXE): $(OBJ) | $(BIN_DIR) # normal-prerequisites | order-only-prerequisites (no out of date check)
	$(CC) $(LDFLAGS) $^ -o $@
	dsymutil $@ # run dsymutil to extract debug info into seperate file

# All compilation steps except linking for every source file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean for rebuilt - Using implicit variable RM (rm -f)
clean:
	@$(RM) -r $(OBJ_DIR) $(BIN_DIR)

# Make sure directories exist
$(OBJ_DIR) $(BIN_DIR) $(BASE_OBJ_DIR) $(BASE_LIB_DIR):
	mkdir -p $@

# check header files for changes
-include $(OBJ:.o=.d)
