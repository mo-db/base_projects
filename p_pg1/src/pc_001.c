#include <stdio.h>
#include <assert.h>

typedef struct hobby {
	char* name;
	struct hobby* next;
} hobby;

typedef struct {
	char* name;
	int age;
	hobby* hobbies;
} person;

int get_lines_n(FILE* fp)
{
	size_t len = 0;
	char* lineptr = NULL;
	int count = 0;
	// ** enables getline to realloc, modify the buffer
	// * would only let it modify the copy
	while (getline(&lineptr, &len, fp) > 0) {
		count++;
	}
	return count;
}

int main(int argc, char* argv[])
{
	FILE* fp = fopen("./src/pc_001-input.txt", "r");
	if (!fp) { printf("ERROR:\n"); return 1; }
	
	int line_count = 0;
	if (!(line_count = get_lines_n(fp))) {
		printf("ERROR:\n"); return 1;
	}

	printf("Number of lines: %d\n", line_count);

	fclose(fp);
	return 0;
}
