#include "int-list.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
    List* arglist = list_create();
    printf("List empty: %d\n", list_empty(arglist));
    for (int i = 1; i < argc; i++) {
        /* if (!list_prepend(arglist, argv[i])) { */
        /*     printf("error list_prepend\n"); */
        /*     return 1; */
        /* } */
        if (!list_append(arglist, argv[i])) {
            printf("error list_prepend\n");
            return 1;
        }
    }
    printf("List empty: %d\n", list_empty(arglist));
    printf("List count: %d\n", list_count(arglist));
    list_print(arglist);
    list_destroy(arglist);
    return 0;
}
