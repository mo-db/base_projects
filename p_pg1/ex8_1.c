#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int str_len(char *str)
{
	int c = 0;

	int len;
	for (len = 0; (c = *(str+len)) != '\0'; len++) {
		len++;
	}
	return len;
}

int most_common_char(char *str, int *occ)
{
	int most_common = 0;
	int count = 0;

	int c = 0;
	for (int i = 0; (c = *(str+i)) != '\0'; i++) {
		occ[c]++;
		if (occ[c] > count) {
			most_common = c;	
			count = occ[c];
		}
	}
	return most_common;
}


int main()
{
	const int SCHAR_MAX = 128;
	int occ_count[SCHAR_MAX];
	for (int i = 0; i < SCHAR_MAX; i++) { occ_count[i] = 0; }

	char str[] = "abc\177dddff";
	/* printf("%s", str); */

	/* printf("%d\n", str_len(str)); */
	printf("most common: %c\n", most_common_char(str, occ_count));

	/* for (int i = 0; i < SCHAR_MAX; i++) {  */
	/* 	printf("%d: %d\n", i, occ_count[i]); */
	/* } */
	return 0;
}

