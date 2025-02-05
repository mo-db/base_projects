#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct node {
    char* string;
    struct node* next;
} node;

typedef struct list {
    struct node* head;
    int size;
} list;

list* list_create()
{
    list* l = malloc(sizeof(list));
    if (!l) { return NULL; }
    l->head = NULL;
    l->size = 0;
    return l;
}

int list_prepend(list* l, char* string)
{
    node* new_head = malloc(sizeof(node));
    if (!new_head) { return 0; }
    new_head->next = l->head;
    new_head->string = string;
    l->head = new_head;
    return 1;
}

void list_print(list* l)
{
    node* step = l->head;
    while (step) {
        printf("%s\n", step->string);
        step = step->next;
    }
}
