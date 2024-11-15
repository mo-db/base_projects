#include <stdint.h>
#include <stdio.h>

// getchar converts to int on return, because this way
// it can return EOF (which is system defined) for errors
// or if it reaches end of file. That is because EOF needs
// to be a different valye than any possible char, so an
// other type is needed, int

int get_bin()
{
	int c;
	printf("bin numbers: ");
	while ((c = getchar()) != EOF) {
		if (c == '0' || c == '1') {
			printf("%d, ", c - '0');
		} else {
			break;
		}
	}
	return 0;
}

uint16_t expo(int base, int exponent)
{
	uint16_t number = 1;
	for (int i = 1; i < exponent; i++) {
		number *= base;
	}
	number -= 1;
	number *= base;
	number += 1;
	number += 256;
	return number;

}

int main()
{
	printf("expo: %lu\n", expo(2, 16));
	/* get_bin(); */
	return 0;
}
