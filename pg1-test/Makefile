PROGRAMS = das-k arrow
SRC = $(PROGRAMS:%=%.c) turtle.c

CFLAGS = $(shell pkg-config --cflags gtk+-3.0) -ggdb3 -O0
LIBS   = $(shell pkg-config --libs gtk+-3.0) -lm

.PHONY: all
all: $(PROGRAMS)

%: %.c turtle.c turtle.h
	gcc -std=c99 $(CFLAGS) $< turtle.c $(LIBS) -o $@

clean:
	rm $(PROGRAMS)
