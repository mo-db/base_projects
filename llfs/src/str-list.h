#ifndef LIST_H
#define LIST_H

// Opaque pointer to the list structure
typedef struct list List;

// Create a new list
List* list_create();

// Destroy a list and free its memory
void list_destroy(List* list);

// Add an element to the tail of the list
int list_append(List* list, char* string);

// Add an element to the head of the list
int list_prepend(List* list, char* string);

// Remove an element from the list
void list_remove(List* list, char* string);

// Print the list (useful for testing)
void list_print(List* list);

// Get the size of the list
int list_count(List* list);

// Check if the list is empty
int list_empty(List* list);

#endif // LIST_H
