#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *todofile = ".todo";

char **todolist = NULL;
int items_allocated = 10;
int item_increase = 10;
int items_in_list = 0;

void add_todo_item(char *text); // kommt später, hier nur zur info an den compiler

// read from file to list
void read_todo_list(void) {
	todolist = malloc(sizeof(char*)*items_allocated);

	FILE *f = fopen(todofile, "r");
	char *line = NULL;
	size_t buffersize = 0;
	int chars_read = 0;
	while ((chars_read = getline(&line, &buffersize, f)) != -1) {
		line[chars_read-1] = '\0';
		add_todo_item(line);
	}
	free(line);
	fclose(f);
}

// save list to file
void write_todo_list(void) {
	FILE *f = fopen(todofile, "w");
	for (int i = 0; i < items_in_list; ++i)
		fprintf(f, "%s\n", todolist[i]);
	fclose(f);
}

void free_todolist(void) {
	for (int i = 0; i < items_in_list; ++i) {
		// printf("freeing todo item (%d) %s\n", i, todolist[i]);
		free(todolist[i]);
	}
	free(todolist);
}

void print_todo_list(void) {
	for (int i = 0; i < items_in_list; ++i)
		printf("%2d: %s\n", i+1, todolist[i]);
}

void print_todo_item_count(void) {
	printf("%d\n", items_in_list);
}

void remove_todo_item(int n) {
	if (n <= 0 || n > items_in_list) {
		fprintf(stderr, "No such item\n");
		exit(-1);
	}
	for (int i = n; i < items_in_list; ++i)
		todolist[n-1] = todolist[n];
	todolist[items_in_list-1] = NULL;
	items_in_list--;
}

void add_todo_item(char *text) {
	if (items_in_list == items_allocated) {
		int new_item_count = items_allocated + item_increase;
		char **new_mem = malloc(sizeof(char*)*new_item_count);
		for (int i = 0; i < items_in_list; ++i)
			new_mem[i] = todolist[i];
		free(todolist);
		todolist = new_mem;
		items_allocated = new_item_count;
	}
	todolist[items_in_list++] = strdup(text);
}

int main(int argc, char **argv) {
	read_todo_list();
	if (argc == 1) {
		print_todo_list();
	}
	else if (argc == 2) {
		if (strcmp(argv[1], "count") == 0)
			print_todo_item_count();
		else
			add_todo_item(argv[1]);
	}
	else if (argc == 3) {
		if (strcmp(argv[1], "done") == 0) {
			int to_remove = atoi(argv[2]);
			if (to_remove == 0) {
				fprintf(stderr, "command done needs a number\n");
				free_todolist();
				return -1;
			}
			remove_todo_item(to_remove);
		}
		else {
			fprintf(stderr, "Not implemented, yet :(\n");
			//add_todo_item(argv[1]);
		}
	}
	else {
		fprintf(stderr, "Not implemented, yet :(\n");
	}
	write_todo_list();
	free_todolist();
}
