### Actual Project
SRC_FILES := main video
SRC_DIR := p_raster

SDL2_CFLAGS := $(shell sdl2-config --cflags)
SDL2_LDFLAGS:= $(shell sdl2-config --static-libs)

# -g = include debug info, -O0/1/2 = optimization
# -MMD -MP to create .d files for header deps
CFLAGS := -Wall -g -MMD -MP $(SDL2_CFLAGS)
LDFLAGS := -L./base/lib -lbase $(SDL2_LDFLAGS)

OBJ_DIR := obj
BIN_DIR := bin
EXE := $(BIN_DIR)/a.out

# OBJ holds all .o files that are given or *.o if none are given
# strip to make sure that " " are not count
ifneq ($(strip $(SRC_FILES)),)
	OBJ := $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC_FILES)))
else
	SRC := $(wildcard $(SRC_DIR)/*.c)
	OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
endif


### Codebase
BASE_SRC_FILES:=
BASE_DIR := base

BASE_CFLAGS := -Wall -g -MMD -MP

BASE_SRC_DIR := $(BASE_DIR)/src
BASE_OBJ_DIR := $(BASE_DIR)/obj
BASE_LIB_DIR := $(BASE_DIR)/lib
BASE_INCLUDE_DIR := $(BASE_DIR)/include
LIB := $(BASE_LIB_DIR)/libbase.a

# BASE_OBJ same as above for OBJ
ifneq ($(strip $(BASE_SRC_FILES)),)
	BASE_OBJ := $(addprefix $(BASE_OBJ_DIR)/, $(addsuffix .o, $(BASE_SRC_FILES)))
else
	BASE_SRC := $(wildcard $(BASE_SRC_DIR)/*.c)
	BASE_OBJ := $(BASE_SRC:$(BASE_SRC_DIR)/%.c=$(BASE_OBJ_DIR)/%.o)
endif



### Targets
# Phony targets aren't treated as files
.PHONY: all base run clean single

# Default target, executed with 'make' command
project: $(EXE)

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


# the target for building the codebase library
base: $(LIB)

$(LIB): $(BASE_OBJ) | $(BASE_LIB_DIR)
	ar -rc $@ $(BASE_OBJ)

$(BASE_OBJ_DIR)/%.o: $(BASE_SRC_DIR)/%.c | $(BASE_OBJ_DIR)
	$(CC) $(BASE_CFLAGS) -c $< -I./$(BASE_INCLUDE_DIR) -o $@


# Clean for rebuilt - Using implicit variable RM (rm -f)
clean:
	@$(RM) -r $(OBJ_DIR) $(BIN_DIR)
	@$(RM) $(BASE_OBJ_DIR)/* $(BASE_LIB_DIR)/*

# Make sure directories exist
$(OBJ_DIR) $(BIN_DIR) $(BASE_OBJ_DIR) $(BASE_LIB_DIR):
	mkdir -p $@



### other stuff
# check header files for changes
-include $(OBJ:.o=.d)
-include $(BASE_OBJ:.o=.d)
