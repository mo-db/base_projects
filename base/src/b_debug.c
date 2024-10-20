#include "../include/libbase.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <assert.h>

FILE *warn_log;
FILE *trace_log;

int base_log_init()
{
	warn_log = fopen(BASE_WARN_LOG, "w+");
	if (!warn_log) {
		fprintf(stderr, "could not create warn_log");
		return 0;
	}
	trace_log = fopen(BASE_TRACE_LOG, "w+");
	if (!trace_log) {
		fprintf(stderr, "could not create trace_log");
		return 0;
	}
	return 1;
}

void _gen_msg(int select, char *time, char *file, int line, char *msg, ...)
{
	// maybe subst_msg as pointer in log_init?
	char subst_msg[BASE_DEBUG_SUBST_MSG_MAXLEN];
	for (int i = 0; i < sizeof(subst_msg); i++) {
		subst_msg[i] = '\0';
	}
	char double_buf[BASE_DEBUG_NUM_MAX];
	char trunc_buf[] = "__TRUNCATED__";
	int subst_msg_iterator = 0;

	int i_val = 0;
	int i_digits;
	double d_val = 0;

	va_list ap; // va_list pointer to iterate trough the va_args
	va_start(ap, msg); // ap now points to msg so that it can progress to the following args
	
	for (char *p = msg; *p; p++) {
		if (*p != '%') {
			subst_msg[subst_msg_iterator++] = *p;
			continue;
		}
		switch (*(++p)) {
			case 'd':
				i_val = va_arg(ap, int);
				for (i_digits = 0; (i_val / pow(10, i_digits)) >= 1; i_digits++)
					; // do nothing
				// check number length, truncate if needed to keep log clean
				if (i_digits > BASE_DEBUG_NUM_MAX) {
					i_digits = BASE_DEBUG_NUM_MAX;
					for (int i = 0; i < (sizeof(trunc_buf) - 1); i++) {
						subst_msg[subst_msg_iterator++] = trunc_buf[i];
					}
				}
				// insert int into subst_msg
				for (; i_digits > 0; i_digits--) {
					int division_portion = (i_val / pow(10, (i_digits - 1)));
					subst_msg[subst_msg_iterator++] = division_portion + '0';
					i_val -= division_portion * pow(10, (i_digits - 1));
					assert(i_val >= 0);
				}
				break;
			case 'f':
				d_val = va_arg(ap, double);
				int cut, len;
				// check number length,truncate if needed to keep log clean
				len = snprintf(NULL, 0, "%.4f", d_val);
				if (len > BASE_DEBUG_NUM_MAX) {
					for (int i = 0; i < (sizeof(trunc_buf) - 1); i++) {
						subst_msg[subst_msg_iterator++] = trunc_buf[i];
					}
				}
				// insert float into subst_msg
				snprintf(double_buf, BASE_DEBUG_NUM_MAX, "%.4f", d_val);
				for (cut = 0; double_buf[cut] != '\0'; cut++)
					;
				for (int i = 0; i < cut; i++) { // (len - 1) to cut /0 that would exit loop
					subst_msg[subst_msg_iterator++] = double_buf[i];
				}
				break;
			default:
				subst_msg[subst_msg_iterator++] = *p;
				break;
		}
	}
	switch (select) {
		case 1:
			fprintf(stderr, "[%s] [%s:%d] %s\n", time, file, line, subst_msg);
			break;
		case 2:
			fprintf(warn_log, "[%s] [%s:%d] %s\n", time, file, line, subst_msg);
			fprintf(stdout, "[%s] [%s:%d] %s\n", time, file, line, subst_msg);
			fflush(warn_log); // writes all data left in FILE buffer
			break;
		case 3:
			fprintf(trace_log, "[%s] [%s:%d] %s\n", time, file, line, subst_msg);
			fflush(trace_log); // writes all data left in FILE buffer
			break;
	}
	va_end(ap);
}
