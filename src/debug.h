#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <SDL2/SDL.h>

#define ERROR_LOGFILE "/Users/moritz/Repos" \
	"/software_renderer/bin/error.log"
#define TRACE_LOGFILE "/Users/moritz/Repos" \
	"/software_renderer/bin/trace.log"
#define PROCESS_ERROR(msg) _process_error(__TIME__, __FILE__, __LINE__, msg)
#define LOG_TRACE(msg) _log_trace(__TIME__, __FILE__, __LINE__, msg)

int log_init(const char * error_log_file, const char * trace_log_file);
void _process_error(char *time, char *file, int line, char *msg);
void _log_trace(char *time, char *file, int line, char *msg);

#endif
