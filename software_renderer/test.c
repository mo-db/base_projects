#include "../base/include/libbase.h"
#include <stdio.h>

int main()
{
	if (!log_init()) { fprintf(stdout, "error log_init"); };
	PROCESS_WARN("a warning test");
	return 0;
}
