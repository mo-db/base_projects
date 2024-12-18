#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_MAX 1000

int main(int argc, char* argv[])
{
	int input_stream[INPUT_MAX];

	if (argc > 1) {
		int input_stream_counter = 0;
		int c;
		for (int i = 1; i < argc; i++) {
			while ((c = *(argv[i]++)) != '\n') {
				input_stream[input_stream_counter++] = c;
			}
		}
	}

	/* char test_str[] = {'\xe4','\xbd','\xa0','\xe5','\xa5','\xbd','\0'}; */
	/* for (int i = 0; i < 20; i++) { */
	/* 	printf("%i ", *(*argv+i)); */
	/* } */
	/* printf("\n"); */
	/* for (int i = 0; i < 20 && test_str[i] != '\0'; i ++) { */
	/* 	printf("%i ", test_str[i]); */
	/* } */

	return 0;
}

