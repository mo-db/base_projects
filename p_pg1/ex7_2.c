#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// prints out a diagram of the occurences of rand numbers modulo m
void rand_hist(int n, int m)
{
	int n_ary[m];
	for (int i = 0; i < m; i++) { n_ary[i] = 0; }
	for (int i = 0; i < n; i++) {
		n_ary[rand()%m]++;
	}
	int most_frequent = 0;
	for (int i = 0; i < (m-1); i++) {
		if (n_ary[i] > most_frequent) { most_frequent = n_ary[i]; }
	}

	// print the stars with a scaling factor
	const int SCALE = 10;
	for (int i = (most_frequent / SCALE); i > 0; i--) {
		for (int j = 0; j < m; j++) {
			if (((n_ary[j] / SCALE) - i) >= 0) {
				printf("**  ");
			} else {
				printf("   ");
			}
		}
		printf("\n");
	}
	for (int i = 0; i < m; i++) {
		printf("%.3d ", n_ary[i]);
	}
}

int main()
{
	const int MODUL = 10;
	const int N_RUNS = 500;

	srand(time(NULL));
	rand_hist(N_RUNS, MODUL);

	return 0;
}

