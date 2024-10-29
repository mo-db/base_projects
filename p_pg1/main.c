#include <stdio.h>

#define TRUE 1
#define FALSE 0

int recursive_pow(int base, int exponent)
{
	if (exponent > 1) {
		exponent--;
		return base * recursive_pow(base, exponent);
	} else if (exponent == 1) {
		return base;
	} else {
		// this only happends when the function is called with exponent 0
		return 1;
	}
}

// my complicated code
int my_print_binary_from_int(int number)
{
	static int n = 1;
	int rem = 0;
	int pow = recursive_pow(2, n);

	// true until the first pow(2,n) > number is found -> skip
	int skip = TRUE;
	if (number / recursive_pow(2, n) >= 1) {
		skip = FALSE;
		n++;
		rem = my_print_binary_from_int(number);
	}
	
	if (rem  != 0 && (rem / (pow / 2)) < 1) {
		printf("%d", 0);
	} else if (rem != 0 && (rem / (pow / 2)) >= 1) {
		printf("%d", 1);
		rem %= (pow / 2);
	// activates for first bin digit
	} else if (rem == 0 && skip) {
		printf("%d", 1);
		rem = number % (pow / 2);
	// fills up the last binary digits
	} else if (rem == 0) {
		printf("%d", 0);
	}
	return rem;
}

// AI generated s**t that is way better...
void print_binary_recursive(int number) {
    // Base case
    if (number == 0) {
        return;
    }
    
    // Recursive call first (this will print digits from left to right)
    print_binary_recursive(number / 2);
    
    // Print current digit
    printf("%d", number % 2);
}

int main()
{

	print_binary_recursive(10);
	/* printf("expected return: %d\n", my_print_binary_from_int(4095)); */
	return 0;
}
