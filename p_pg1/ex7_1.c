#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../base/include/libbase.h"

// swaps two valuse if the first is smaller then the second
void min_max_swap(int *v1, int *v2)
{
	printf("try swap: %d witch %d -> ", *v1, *v2);
	int vtmp;
	if (*v1 >= *v2) {
		vtmp = *v1;
		*v1 = *v2;
		*v2 = vtmp;
		printf("swapped!\n");
	} else {
		printf("not swapped!\n");
	}
}

void sort5(int v1, int v2, int v3, int v4, int v5)
{
	int temp_ary[] = {v1, v2, v3, v4, v5};
	int lines = 5;
	int depth_start = 2;
	int depth = lines - depth_start;

	//printing out
	printf("lines: ");
	for (int k = 0; k < lines; k++) {
		printf("%d, ", temp_ary[k]);
	}
	printf("\n");


	for (int i = 0; i < depth; i++) {


		for (int j = 0; j < (i+depth_start); j++) {
			min_max_swap(&temp_ary[j], &temp_ary[lines-(i+depth_start)+j]);
		}

		//printing out
		printf("lines: ");
		for (int k = 0; k < lines; k++) {
			printf("%d, ", temp_ary[k]);
		}
		printf("\n");

	}
}

// first argument must be int and must be given!
int main(int argc, char **argv)
{
	// Convert first argument to integer
	const int NUM_MAX_DIGITS = 15;
	int num_val = 0;
	if (argc > 1) {
		int argv_deref;
		int i = 0;
		while ((argv_deref = *(argv[1] + i++)) != '\0') {
			assert(i <= NUM_MAX_DIGITS);
			if (argv_deref >= '0' && argv_deref <= '9') {
				num_val *= 10; 
				num_val += argv_deref - '0';
			} else {
				/* printf("non-digit found in first arg!\n"); */
				BASE_PROCESS_ERROR("non-digit found in first arg!");
				return 1;
			}
		}
	} else {
		printf("no argument given!\n");
	}



	printf("num_val: %d\n", num_val);
	/* sort5(7, 4000, 1, -9, 3); */
	return 0;
}
