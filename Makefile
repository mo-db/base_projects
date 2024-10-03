### CONFIG
# specify source files: if no specified -> fetches all source files
FILES := testrl

# Makefile needs tab not spaces before recepie command
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

# strip to make sure that " " are not count
# when checking if files are specified, else fetch all
ifneq ($(strip $(FILES)),)
	SRC := $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(FILES)))
	OBJ := $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(FILES)))
else
	SRC := $(wildcard $(SRC_DIR)/*.c)
	OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
endif
EXE := $(BIN_DIR)/a.out

# Helper vars
# SDL_CFLAGS := $(shell pkg-config --cflags sdl3)
# SDL_LIBS := $(shell pkg-config --libs sdl3)
RL_FLAGS := -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL ~/Libs/lib/libraylib.a

# -g = include debug info, -O0/1/2 = optimization
# -MMD -MP to create .d files for header deps
CFLAGS := -Wall -g -MMD -MP $(CPPFLAGS)
LDFLAGS := $(LDFLAGS) $(RL_FLAGS)
LIBS :=



### MAIN BUILD PROCESS
# Phony targets aren't treated as files
.PHONY: all run clean single

# Default target, executed with 'make' command
all: $(EXE)

# run dsymutil to extract debug info into seperate file
# Linking the object files, building executable
$(EXE): $(OBJ) | $(BIN_DIR) $(SRC_DIR)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS)
	dsymutil $@

# All compilation steps except linking for every source file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR) $(SRC_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# check header files for changes
-include $(OBJ:.o=.d)



### OTHER TARGETS
# make and execute
run: $(EXE)
	./bin/a.out

# to be able to debug a single file, -E = run preprocessor only
single:
	$(CC) $(CFLAGS) -E $(SRC_DIR)/debug.c | tee single.info

# Using implicit variable RM (rm -f)
clean:
	@$(RM) -r $(OBJ_DIR) $(BIN_DIR)
	@$(RM) single.info

# Make sure directories exist
# targets : normal-prerequisites | order-only-prerequisites
# order-only-prerequisites are never checked for out of date
# they are ckecked before the target is built
$(SRC_DIR) $(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@
