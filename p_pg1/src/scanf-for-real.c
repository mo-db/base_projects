#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Bitte sag mir wenigstens welches File\n");
		return -1;
	}
	FILE *f = fopen(argv[1], "r");
	// if (f == NULL) { // anfängerfreundlich
	if (!f) {           // kanonisch
		perror("Cannot open file");
		return -1;
	}
	int w, h, chars_read = 0;
	int elements_read = fscanf(f, "P3 %d %d 255 %n", &w, &h, &chars_read);
	if (chars_read == 0) {
		fprintf(stderr, "Image header seems broken\n");
		fclose(f);
		return -1;
	}
	printf("%s: %d x %d\n", argv[1], w, h);
	fclose(f);
	return 0;
}
