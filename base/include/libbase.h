#ifndef LIBBASE_H
#define LIBBASE_H


#include <stdio.h>
//#include <SDL2/SDL.h>


// INFO: b_debug
#define B_WARN_LOG "bin/warn.log"
#define B_TRACE_LOG "bin/trace.log"

#define B_DEBUG_SUBST_MSG_MAXLEN 200
#define B_DEBUG_NUM_MAX 20

// ## before __VA_ARGS__ needed to remove the , if no args are given so it compiles
#define B_PROCESS_ERROR(msg, ...) _gen_msg(1, __TIME__, __FILE__, __LINE__, msg, ##__VA_ARGS__)
#define B_PROCESS_WARN(msg, ...) _gen_msg(2, __TIME__, __FILE__, __LINE__, msg, ##__VA_ARGS__)
#define B_PROCESS_TRACE(msg, ...) _gen_msg(3, __TIME__, __FILE__, __LINE__, msg, ##__VA_ARGS__)

// create the log files and initialize some things
int b_log_init();

// clang format attribute (same as gcc) to handle like printf function -> linting
__attribute__((__format__(__printf__, 5, 6)))
// this function is called by the respective macro
void _gen_msg(int select, char *time, char *file, int line, char *msg, ...);


#endif
