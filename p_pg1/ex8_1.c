#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SCHAR_MAX 128

int str_len(char *str)
{
	int c = 0;

	int len;
	for (len = 0; (c = *(str+len)) != '\0'; len++) {
		;
	}
	return len;
}

int char_occ_count(char *str, int *occ)
{
	int most_common = 0;
	int occ_count = 0;

	int c = 0;
	int i = 0;
	while ((c = str[i++]) != '\0') {
		occ[c]++;
		if (occ[c] > occ_count) {
			most_common = c;
			occ_count = occ[c];
		}
	}
	return most_common;
}

//TODO: maybe experiment with different solutions for input
// getchar, sscanf, fgets, fgetc
// fgets() and gets_s()
int stdin_char_occ_count(int *occ)
{
	int most_common = 0;
	int occ_count = 0;

	char c;
	while ((c = getchar()) != '\0' && c != EOF) {
		if (c == ' ') {
			continue; 
		} else {
			occ[c]++;
			if (occ[c] > occ_count) {
				most_common = c;
				occ_count = occ[c];
			}
		}
	}
	return most_common;
}

int ascii_occ_histogram(char *str, int *occ, char most_common)
{
	// print the stars with a scaling factor
	// only print certain ascii values in the histogram
	const int SCALE = 1;
	int ascii_start = 48;
	for (int i = ascii_start; i < SCHAR_MAX-1; i++) {
		printf("%c ", i);
		for (int j = 0; j < (occ[i] / SCALE); j++) {
			printf("*");
		}
		printf("\n");
	}
	return 1;
}

int bad_sorting(char *str)
{
	int i;
	while (1) {
		i = 0;
		while (1) {
			if (str[i++] 
		}
	}
	return 0;
}

int main()
{
	char str[] = "abc\176dddff";

	// define occurence ary and init with 0's
	int occ_count[SCHAR_MAX];
	char most_common;
	for (int i = 0; i < SCHAR_MAX; i++) { occ_count[i] = 0; }

	// this function fills occ_ary and returns the most common char
	most_common = stdin_char_occ_count(occ_count);
	ascii_occ_histogram(str, occ_count, most_common);

	/* printf("%s\n", str); */
	/* printf("%d\n", str_len(str)); */
	/* printf("most common: %c\n", most_common); */

	return 0;
}
