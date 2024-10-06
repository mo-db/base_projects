#include "debug.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <assert.h>
#include <SDL2/SDL.h>

FILE *warn_log;
FILE *trace_log;

int log_init(const char *warn_logfile, const char *trace_logfile)
{
	warn_log = fopen(warn_logfile, "w+");
	if (!warn_log) {
		fprintf(stderr, "could not create warn_log");
		return 0;
	}
	trace_log = fopen(trace_logfile, "w+");
	if (!trace_log) {
		fprintf(stderr, "could not create trace_log");
		return 0;
	}
	return 1;
}

/* void _process_error(char *time, char *file, int line, char *msg) */
/* { */
/* 	fprintf(stderr, "[%s] [%s:%d] %s\n", time, file, line, msg); */
/* 	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, SDL_GetError(), msg, NULL); // if window exists attach to window */
/* 	fprintf(error_log, "[%s] [%s:%d] %s\n", time, file, line, msg); */
/* 	// file handling functions use syscalls = slow, these functions use a buffer */
/* 	// in the background (set different modes with setbuf()) */
/* 	fflush(error_log); // writes all data left in FILE buffer */
/* } */

void _log_trace(char *time, char *file, int line, char *msg)
{
	fprintf(trace_log, "[%s] [%s:%d] %s\n", time, file, line, msg);
	fflush(trace_log); // writes all data left in FILE buffer
}

// TODO: better errorhandling, print no 0 after float, 
void _process_warn(char *time, char *file, int line, char *msg, ...)
{
	char subst_msg[SUBST_MSG_MAXLEN];
	char double_buf[NUM_MAXELN];
	int subst_msg_iterator = 0;

	int i_val = 0;
	int i_digits;
	double d_val = 0;

	va_list arg_p; // init a variable of va_list type to point it to the list later
	va_start(arg_p, msg); // arg_p now points to msg so that it can progress to the following args
	
	for (char *p = msg; *p; p++) {
		if (*p != '%') {
			subst_msg[subst_msg_iterator++] = *p;
			continue;
		}
		switch (*(++p)) {
			case 'd':
				i_val = va_arg(arg_p, int);
				// int to character string
				for (i_digits = 0; (i_val / pow(10, i_digits)) >= 1; i_digits++)
					; // do nothing
				for (; i_digits > 0; i_digits--) {
					// TODO: nochmal exact nachschauen wieso ascii 0 den int zu char macht
					int division_portion = (i_val / pow(10, (i_digits - 1))); // zwischenval NAME!!!
					subst_msg[subst_msg_iterator++] = division_portion + '0';
					i_val -= division_portion * pow(10, (i_digits - 1));
					assert(i_val >= 0);
				}
				break;
			case 'f':
				d_val = va_arg(arg_p, double);
				int len = snprintf(NULL, 0, "%f", d_val);
				if (len > NUM_MAXELN) {
					len = NUM_MAXELN; // truncate number if to big - log?
				}
				snprintf(double_buf, len, "%f", d_val);
				for (int i = 0; i < len; i++) {
					subst_msg[subst_msg_iterator++] = double_buf[i];
				}
				break;

			// ival to character string and wirte into msg_string
			default:
				subst_msg[subst_msg_iterator++] = *p;
				break;
		}
	}
	fprintf(warn_log, "[%s] [%s:%d] %s\n", time, file, line, subst_msg);
	fprintf(stdout, "[%s] [%s:%d] %s\n", time, file, line, subst_msg);
	fflush(warn_log); // writes all data left in FILE buffer
}
