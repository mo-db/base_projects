#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// variant without linked lists

// expects that the last line ends with a newline (\n) character
// (this is common practice)
int number_of_lines_in_file(char *filename) {
	FILE *in = fopen(filename, "r");
	if (!in) {
		perror("Cannot open input file");
		exit(-1);
	}
	int lines = 0;
	int c;
	while (c = getc(in), c != EOF)
		if (c == '\n')
			lines++;
	fclose(in);
	return lines;
}

// returns if all went well
// we have to clean up resources after this call!
bool read_lines(char *filename, int count, int *left, int *right) {
	FILE *in = fopen(filename, "r");
	// we should be defensive here and check if we can open the file,
	// it might no longer be there and this way we get a sensible error
	// message for this corner case
	if (!in) {
		perror("Cannot open input file");
		return false;
	}
	// now read in the lines, each consisting of one entry for the 
	// `left' array and one entry for the `right' array.
	for (int i = 0; i < count; ++i)
		if (fscanf(in, "%d %d", left+i, right+i) != 2) {
			fprintf(stderr, "Not enough items in the file (at line %d)\n", i);
			fclose(in);
			return false;
		}
	fclose(in);
	// for debugging:
	// printf("L: "); for (int i = 0; i < count; ++i) printf(" %5d", left[i]);  printf("\n");
	// printf("R: "); for (int i = 0; i < count; ++i) printf(" %5d", right[i]); printf("\n");
	return true;
}

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

// helper
int find_and_swap_min(int starting_pos, int *data, int elements) {
	int smallest_pos = starting_pos;
	for (int i = starting_pos+1; i < elements; ++i)
		if (data[i] < data[smallest_pos])
			smallest_pos = i;
	swap(data+starting_pos, data+smallest_pos);
	return data[starting_pos];
}

// idea:
// - for the first distance:
//   - find smallest element of left and right
//   - swap to first position
//   - compute distance between them
// - for the second distance:
//   - find smallest element in left and right,
//     but after the first one
//   - proceed as before
// - keep incrementing until no elements are left
long calc_distance(int *left, int *right, int entries) {
	long distance = 0;
	for (int i = 0; i < entries; ++i) {
		long min_left  = find_and_swap_min(i, left,  entries);
		long min_right = find_and_swap_min(i, right, entries);
		distance += abs(min_right - min_left);
	}
	return distance;
}

long count_occurences(int value, int *list, int entries) {
	int count = 0;
	for (int i = 0; i < entries; ++i)
		if (list[i] == value)
			count++;
	return count;
}

long similarity_score(int *left, int *right, int entries) {
	long sum = 0;
	for (int i = 0; i < entries; ++i)
		sum += left[i] * count_occurences(left[i], right, entries);
	return sum;
}

// takes input filename via cmdline arg
int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "I need an input file name to work on the problem\n");
		return -1;
	}
	char *filename = argv[1];
	int lines = number_of_lines_in_file(filename);
	printf("lines: %d\n", lines);

	int *left  = malloc(sizeof(unsigned int)*lines),
	    *right = malloc(sizeof(unsigned int)*lines);
	if (read_lines(filename, lines, left, right)) {
		// we could read the file, this is expected but might fail, see above.
		// printf("%ld\n", calc_distance(left, right, lines));
		printf("%ld\n", similarity_score(left, right, lines));
	}

	free(left);
	free(right);
}

