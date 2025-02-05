#ifndef LIST_H
#define LIST_H

// Opaque pointer to the list structure
typedef struct list list;

// Create a new list
list* list_create();

// Destroy a list and free its memory
void list_destroy(list* l);

// Add element to tail
int list_append(list* l, char* string);

// Add element to head
int list_prepend(list* l, char* string);

// Remove an element from the list
void list_remove(list* l, int value);

// Print the list (useful for testing)
void list_print(list* l);

// Get the size of the list
int list_size(const list* l);

// Check if the list contains a value
int list_empty(const list* l, int value);

#endif
