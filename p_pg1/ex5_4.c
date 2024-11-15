#include <stdio.h>

// calculate the n-th number of the fobonacci series, using recursion
int fib(int n)
{
	int sum;
	if (n < 2) {
		return n;	
	}
	return (fib(n-1) + fib(n-2));
}

// calculate the n-th number of the fobonacci series, using while
int fib_iter(int n)
{
	int num1 = 0;
	int num2 = 1;
	int sum;

	int iter = 2;
	while(iter++ < n) {
		sum = num1 + num2;
		num1 = num2;
		num2 = sum;
	}
	return sum;
}

int main()
{
	int fib_nuber = 6;
	/* printf("%d-th fib: %d\n", fib_nuber, fib(fib_nuber)); */
	printf("%d-th fib: %d\n", fib_nuber, fib_iter(fib_nuber));
	return 0;
}
