#include "../base/include/libbase.h"
#include <stdio.h>

int main()
{
	if (!b_log_init()) { fprintf(stdout, "error log_init"); };
	B_PROCESS_WARN("a warning test");
	return 0;
}
