#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// mit valgrind probieren

char* todo_file = "vl_16.todo";

// todolist in ein char** ary einlesen und dann bearbeiten


// selgrad benutzt getline, also free(line) muss benutzt werden
// todolist mallocen auf 10 und dann reallocen
void read_todo_list(void)
{}

//
void print_todo_list(void) 
{
	printf("list\n");
}

// gleiche struktur wie printen
void print_todo_item_count(void)
{
	printf("print item count\n");
}

void remove_todo_item(int n)
{
	printf("remove item\n");
}

// open todofile in append mode
void add_todo_item(char* text)
{
	printf("add item\n");
}


int main(int argc, char* argv[])
{
	// scanf, find out when it stops -> does ungetc work here?
	
	if (argc == 1) {
		print_todo_list();
	} else if (argc == 2) {
		if (strcmp(argv[1], "count") == 0) {
			print_todo_item_count();
		} else {
			add_todo_item(argv[1]);
		}
	} else if (argc == 3 ){
		if (strcmp(argv[1], "done") == 0) {
			int remove = atoi(argv[2]);
			if (remove == 0) {
				fprintf(stderr, "command done needs a number\n");
				return -1;
			}
			remove_todo_item(1);
		} else {
			fprintf(stderr, "not implemented, yet\n");
			add_todo_item(argv[1]);
		}
	} else {
			fprintf(stderr, "not implemented, yet\n");
	}
	return 0;
}


