#include <assert.h>
#include <stdint.h>
#include <stdio.h>

// getchar converts to int on return, because this way
// it can return EOF (which is system defined) for errors
// or if it reaches end of file. That is because EOF needs
// to be a different valye than any possible char, so an
// other type is needed, int

// zur letzten Aufgabe:
// Ja es gibt ein Schema:
// variablen der gleichen typen haben adressen,
// bei denen die letzten stellen aehnlich sind

// read binary values and convert to dec using + and *
// binary values input needs to be reversed?! bc. no array?!
void read_bin_to_dec()
{
	int c;
	int exponent_val = 1;
	int dec_sum = 0;
	int multi_counter = 0;

	printf("bin number: ");
	while ((c = getchar()) != EOF) {
		if (c == '0' || c == '1') {

			if (c == '1') {
				// need to multi one more than there are 0's
				multi_counter++;
				while (multi_counter > 0) {
					if (exponent_val == 1) {
						multi_counter--;
					}
					exponent_val *= 2;
					multi_counter--;
				}
				dec_sum += exponent_val;
			} else {
				multi_counter++;
			}

			// print until c is no binary value
			printf("%d, ", (c - '0'));
		} else {
			printf("\n%c is not binary!", c);
			break;
		}
	}
	printf("\nconverted to dec via multiplication:\n%d", dec_sum);
	printf("\nconverted to dec via bitweise:\n%d", dec_sum);
	printf("\n");
}

void read_bin_to_dec_bitweise() {
	int sum = 0;

	int c;
	printf("binary: ");
	/* while ((c = getchar()) != EOF && c != '\n') { */
	while ((c = getchar()) != EOF) {
		assert(sum >= 0);

		// convert c to 0 or 1
		int conf_c = (c - '0');

		if (c == '0' || c == '1') {
			// print the bin digits
			printf("%d", conf_c);

			// ignore trailing 0's, and fill the first 1
			if (sum == 0) {
				sum = (c - '0');
				continue;
			}

			// bitshift,
			// activate the rightmoste bit if 1
			sum <<= 1;
			sum |= conf_c;
		} else if (sum > 0) {
			printf("\ndecimal: %d\n\n", sum);
			printf("binary: ");
			sum = 0;
		} else {
			; // do nothing
		}
	}
	if (sum > 0) {
		printf("\ndecimal: %d\n", sum);
	}
}



/* uint16_t expo(int base, int exponent) */
/* { */
/* 	uint16_t number = 1; */
/* 	for (int i = 1; i < exponent; i++) { */
/* 		number *= base; */
/* 	} */
/* 	number -= 1; */
/* 	number *= base; */
/* 	number += 1; */
/* 	number += 256; */
/* 	return number; */
/**/
/* } */

int main()
{
	/* printf("expo: %lu\n", expo(2, 16)); */
	read_bin_to_dec_bitweise();
	return 0;
}
