#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <SDL2/SDL.h>

#define WARN_LOGFILE "/Users/moritz/Repos" \
	"/software_renderer/bin/warn.log"
#define TRACE_LOGFILE "/Users/moritz/Repos" \
	"/software_renderer/bin/trace.log"

#define SUBST_MSG_MAXLEN 200
#define NUM_MAXELN 20

// ## before __VA_ARGS__ needed to remove the , if no args are given so it compiles
#define PROCESS_ERROR(msg, ...) _gen_msg(1, __TIME__, __FILE__, __LINE__, msg, ##__VA_ARGS__)
#define PROCESS_WARN(msg, ...) _gen_msg(2, __TIME__, __FILE__, __LINE__, msg, ##__VA_ARGS__)
#define PROCESS_TRACE(msg, ...) _gen_msg(3, __TIME__, __FILE__, __LINE__, msg, ##__VA_ARGS__)

int log_init(const char * warn_logfile, const char * trace_logfile);

// clang format attribute (same as gcc) to handle like printf function -> linting
__attribute__((__format__(__printf__, 5, 6)))
void _gen_msg(int select, char *time, char *file, int line, char *msg, ...);

#endif