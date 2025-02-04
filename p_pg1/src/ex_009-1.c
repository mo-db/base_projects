#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_MAX 1000
#define WORD_MAX 100

int main(int argc, char* argv[])
{
	char input_buf[INPUT_MAX];
	char word_buf[WORD_MAX];
	// forbidden word, should be an ary if serious
	char* forb = "bla";

	if (argc > 1) {
		int char_counter = 0;
		int c;
		for (int i = 1; i < argc; i++) {

			// write each arg into a word buffer
	   		int word_counter = 0;
			while ((c = *(argv[i]++)) != '\0') {
				word_buf[word_counter++] = c;
			}
			word_buf[word_counter] = '\0';

			// compare the word in buffer with forbidden word
			// if equal, exit. Else write the word in the input buffer.
			if (strcmp(word_buf, forb) == 0) {
				printf("%s found in string!\n", forb);
				return 1;
			} else {
	  			for (int j = 0; word_buf[j] != '\0'; j++) {
	  				input_buf[char_counter++] = word_buf[j];	
	  			}
	  		}
			input_buf[char_counter++] = ' ';
		}
		input_buf[--char_counter] = '\0';
	}
	printf("Moin, %s.\n", input_buf);
	return 0;
}

