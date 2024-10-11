# TODO: restructure makefile and project, use "make base" to build the library
# folder as static library files

### CONFIG
# specify source files
#PROJECT_FILES := main video objects logic state
PROJECT_FILES :=

# specify the directory names, PROJECT_SRC_DIR is the project, base is my base code
PROJECT_SRC_DIR := software_renderer
OBJ_DIR := obj
BIN_DIR := bin

# create paths PROJECT_FILES, strip to make sure that " " are not count
# check if PROJECT_FILES variable is empty, if so create paths for * files
ifneq ($(strip $(PROJECT_FILES)),)
	#SRC := $(addprefix $(PROJECT_SRC_DIR)/, $(addsuffix .c, $(PROJECT_FILES)))
	OBJ := $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(PROJECT_FILES)))
else
	SRC := $(wildcard $(PROJECT_SRC_DIR)/*.c)
	OBJ := $(SRC:$(PROJECT_SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
endif

# create the paths for BASE_FILES
# SRC := $(SRC) $(addprefix $(BASE_SRC_DIR)/, $(addsuffix .c, $(BASE_FILES)))
# OBJ := $(OBJ) $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(BASE_FILES)))



# the path fo the final executable
EXE := $(BIN_DIR)/a.out

# Helper vars
# SDL3_FLAGS := $(shell pkg-config --libs --cflags sdl3)
SDL2_CFLAGS := $(shell sdl2-config --cflags)
SDL2_LDFLAGS:= $(shell sdl2-config --static-libs)
RL_FLAGS := -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL /usr/local/lib/libraylib.a

# -g = include debug info, -O0/1/2 = optimization
# -MMD -MP to create .d files for header deps
CFLAGS := -Wall -g -MMD -MP $(SDL2_CFLAGS)
LDFLAGS := -L/Users/moritz/Repos/base_projects/base -llibtest $(SDL2_LDFLAGS)

# TODO: make base_lib, make proj

### MAIN BUILD PROCESS
# Phony targets aren't treated as files
.PHONY: all base run clean single

# Default target, executed with 'make' command
project: $(EXE)

# Execute immediatelly after building
run: $(EXE)
	./bin/a.out

# Main executable target for the project
$(EXE): $(OBJ) | $(BIN_DIR) # normal-prerequisites | order-only-prerequisites
	$(CC) $(LDFLAGS) $^ -o $@
	dsymutil $@ # run dsymutil to extract debug info into seperate file

# All compilation steps except linking for every source file
$(OBJ_DIR)/%.o: $(PROJECT_SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


# build codebase library
BASE_SRC:=
BASE_DIR := base
BASE_SRC_DIR := $(BASE_DIR)/src
BASE_OBJ_DIR := $(BASE_DIR)/obj
BASE_LIB_DIR := $(BASE_DIR)/lib
BASE_INCLUDE_DIR := $(BASE_DIR)/include

LIB := $(BASE_LIB_DIR)/libbase.a

ifneq ($(strip $(BASE_SRC)),)
	BASE_OBJ := $(addprefix $(BASE_OBJ_DIR)/, $(addsuffix .o, $(BASE_SRC)))
else
	BASE_SRC := $(wildcard $(BASE_SRC_DIR)/*.c)
	BASE_OBJ := $(BASE_SRC:$(BASE_SRC_DIR)/%.c=$(BASE_OBJ_DIR)/%.o)
endif

base: $(LIB)

$(LIB): $(BASE_OBJ) | $(BASE_LIB_DIR)
	ar -rc $@ $(BASE_OBJ)

$(BASE_OBJ_DIR)/%.o: $(BASE_SRC_DIR)/%.c
	$(CC) -Wall -g -MMD -MP -c $< -I./$(BASE_INCLUDE_DIR) -o $@

# Using implicit variable RM (rm -f)
clean:
	@$(RM) -r $(OBJ_DIR) $(BIN_DIR)
	@$(RM) $(BASE_OBJ_DIR)/*

# Make sure directories exist
# targets : normal-prerequisites | order-only-prerequisites
# order-only-prerequisites are never checked for out of date
# they are ckecked before the target is built
$(PROJECT_SRC_DIR) $(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

# check header files for changes
-include $(OBJ:.o=.d)
-include $(BASE_OBJ:.o=.d)
