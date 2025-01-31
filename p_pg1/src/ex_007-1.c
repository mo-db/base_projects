#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../base/include/libbase.h"

/* #define debug */

// swaps two valuse if the first is smaller then the second
int min_max_swap(int *v1, int *v2)
{
#ifdef debug
	printf("try swap: %d witch %d -> ", *v1, *v2);
#endif
	int vtmp;
	// must be > not >= for bubblesort, else this infinite recursion
	if (*v1 > *v2) {
		vtmp = *v1;
		*v1 = *v2;
		*v2 = vtmp;
#ifdef debug
		printf("swapped!\n");
#endif
		return 1;
	} else {
#ifdef debug
		printf("not swapped!\n");
#endif
		return 0;
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

void b_sort(int *ary, int size)
{
	int has_swapped = 0;
	for (int i = 0; i < (size - 1); i++) {
		has_swapped += min_max_swap(ary+i, ary+i+1);
	}
	if (!has_swapped) { return; }
	b_sort(ary, size);
}

void fill_ary(int *value_ary, int size)
{
	// no error handling or checking if input is int
	for (int i = 0; i < size; i++) {
		scanf("%d", value_ary+i);
	}
}

// first argument must be int and must be given!
int main(int argc, char **argv)
{
	// sort 5 static arguments
	/* sort5(7, 4000, 1, -9, 3); */

	// Convert first argument to integer
	const int NUM_MAX_DIGITS = 15;
	int n_values = 0;
	if (argc > 1) {
		int argv_deref;
		int i = 0;
		while ((argv_deref = *(argv[1] + i++)) != '\0') {
			assert(i <= NUM_MAX_DIGITS);
			if (argv_deref >= '0' && argv_deref <= '9') {
				n_values *= 10; 
				n_values += argv_deref - '0';
			} else {
				/* printf("non-digit found in first arg!\n"); */
				BASE_PROCESS_ERROR("non-digit found in first arg!");
				return 1;
			}
		}
	} else {
		printf("no argument given!\n");
	}
	printf("n_values: %d\n", n_values);

	// allocate memory for array and print it out
	int *value_ary = malloc(sizeof(int) * n_values);
	fill_ary(value_ary, n_values);
	printf("ary: \n");
	for (int i = 0; i < n_values; i++) {
		printf("%d, ", value_ary[i]);
	}
	printf("\n");

	// bublesort implementation
	b_sort(value_ary, n_values);
	printf("sorted ary: \n");
	for (int i = 0; i < n_values; i++) {
		printf("%d, ", value_ary[i]);
	}
	printf("\n");
	return 0;
}
