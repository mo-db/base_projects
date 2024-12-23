#ifndef STATE_H
#define STATE_H

struct Mouse {
    int x;
    int y;
    int scaled_x;
    int scaled_y;
    int down;
};

struct State {
    struct Mouse mouse;
};

// Declare the global state variable for use in other source files
extern struct State state;

#endif
