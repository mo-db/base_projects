#include <stdio.h>
#include <stdint.h>
#include <assert.h>

//--- P01 ---
void sum_multiples_of_3_5()
{
	int sum = 0;
	for (int i = 0; i < 1000; i++) {
		if ((i % 3 == 0) || (i % 5 == 0)) {
			sum += i;
		}
	}
	printf("sum: %d\n", sum);
}

//--- P02 ---
// return the sum all even fibonacci numbers, but only for consider
// number terms under 4 million
// fib numbers: 1,2,3,5,8,13,21,...
void sum_even_fib_below_4mil()
{
	int num_1 = 1; int num_2 = 2;
	int new_num = 0;
	uint64_t sum = 2;
	int keep_going = 0;
	while (1) {
		new_num = num_1 + num_2;
		if (new_num >= 4000000) {
			break;
		} else if (new_num % 2 == 0) {
			sum += new_num;
		}
		num_1 = num_2; num_2 = new_num;
	}
	printf("sum: %llu\n", sum);
}

int main()
{
	//sum_multiples_of_3_5(); // Check
	sum_even_fib_below_4mil();
	return 0;
}


