#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

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
	char* linep = NULL;
	int count = 0;
	while (getline(&linep, &len, fp) > 0) {
		count++;
	}
    rewind(fp); // if not reset fp, cant call getline again!
	return count;
}

// insert node at head of list
hobby* hobby_new(char* name, hobby* next)
{
    hobby* new_hobby = malloc(sizeof(hobby));
    new_hobby->name = strdup(name); // strdump segfaults if NULL pointer!
    new_hobby->next = next;
    return new_hobby;
}
void free_hobbies(hobby* hp)
{
    if (hp != NULL) { 
        free_hobbies(hp->next);
    }
    free(hp);
}

void free_persons(person* pptr, int n)
{
    for (int i = 0; i < n; i++) {
        free_hobbies((pptr+i)->hobbies);
    }
    printf("test: %s\n", pptr[3].hobbies->name);
    free(pptr);
}

void read_line(person* new_person, char* lineptr)
{
    char* token = strtok(lineptr, " ");
    new_person->name = strdup(token); // has to be freed...
    token = strtok(NULL, " ");
    new_person->age = *token;

    new_person->hobbies = NULL;
    while((token = strtok(NULL, ", ")) != NULL) {
        new_person->hobbies = hobby_new(token, new_person->hobbies);
    }
}

int read_file(const char* fname)
{
    FILE* fp = fopen(fname, "r");
	if (!fp) { printf("ERROR:\n"); return 0; }
	printf("file opened\n");

	int line_count = 0;
	if (!(line_count = get_lines_n(fp))) {
		printf("ERROR:\n"); return 0;
	}
	printf("Number of lines: %d\n", line_count);

	size_t len = 0;
	char* lineptr = NULL;

    /* person persons[line_count]; */
    person* persons = malloc(sizeof(person)*line_count);

    for (int i = 0; i < line_count; i++) {
        getline(&lineptr, &len, fp);
        read_line(&persons[i], lineptr);
    }

    // this makes no sense here but this return of person sucks ass
    // prints in the wrong order because i add nodes to head of ll
    for (int i = 0; i < line_count; i++) {
        printf("name: %s\n", persons[i].name);
        printf("name: %d\n", persons[i].age);
        hobby* hp = persons[i].hobbies;
        while (hp) {
            printf("hobby: %s\n", hp->name);
            hp = hp->next;
        }
    }

    free_persons(persons, line_count);
	fclose(fp);
    return 1;
}

int main(int argc, char* argv[])
{
    const char* FNAME = "./ll_ary/hobbies.txt";
    if (!read_file(FNAME)) { return 1;}
	return 0;
}
/* getline: https://www.ibm.com/docs/en/zos/3.1.0?topic=functions-getline-read-entire-line-from-stream */
