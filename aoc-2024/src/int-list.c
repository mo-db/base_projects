#include "int-list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct node {
    int data;
    struct node* next;
} Node;

typedef struct list{
    Node* head;
    int count;
} List;

List* list_create()
{
    List* list = malloc(sizeof(List));
    assert(list != NULL);
    list->head = NULL;
    list->count = 0;
    return list;
}

static void _node_destroy(Node* node)
{
    if (node->next != NULL) { 
        _node_destroy(node->next);
    }
    free(node);
}

void list_destroy(List* list)
{
    assert(list != NULL);
    assert(list->head != NULL);
    _node_destroy(list->head);
    free(list);
}

void list_print(List* list)
{
    Node* current = list->head;
    while (current) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

int list_count(List* list)
{
    assert(list != NULL);
    return list->count;
}

int list_empty(List* list)
{
    assert(list != NULL);
    if (list->head == NULL)
        return 1;
    else
        return 0;
}

// node specific functions
int list_append(List* list, int data)
{
    assert(list != NULL);

    Node* new_node = malloc(sizeof(Node));
    if (!new_node) { return 0; }
    new_node->data = data;
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node* current = list->head;
        for (;;) {
            if (current->next == NULL) {
                current->next = new_node;
                break;
            } else {
                current = current->next;
            }
        }
    }
    list->count++;
    return 1;
}

int list_prepend_char(List* list, int data)
{
    assert(list != NULL);
    Node* new_node = malloc(sizeof(Node));
    if (!new_node) { return 0; }
    // setting to NULL to avoid mem errors
    new_node->data = data;
    new_node->next = NULL;
    // head gets address of new_node, new_node->next gets address of prev node
    new_node->next = list->head;
    list->head = new_node;
    list->count++;
    return 1;
}
