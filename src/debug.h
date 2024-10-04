#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <SDL2/SDL.h>

#define WARN_LOGFILE "/Users/moritz/Repos" \
	"/software_renderer/bin/warn.log"
#define TRACE_LOGFILE "/Users/moritz/Repos" \
	"/software_renderer/bin/trace.log"

#define SUBST_MSG_MAXLEN 200

/* #define PROCESS_ERROR(msg) _process_error(__TIME__, __FILE__, __LINE__, msg) */
#define LOG_TRACE(msg) _log_trace(__TIME__, __FILE__, __LINE__, msg)
#define PROCESS_WARN(msg, ...) _process_warn(__TIME__, __FILE__, __LINE__, msg, __VA_ARGS__)

int log_init(const char * warn_logfile, const char * trace_logfile);
/* void _process_error(char *time, char *file, int line, char *msg); */
void _log_trace(char *time, char *file, int line, char *msg);
void _process_warn(char *time, char *file, int line, char *msg, ...);

#endif
