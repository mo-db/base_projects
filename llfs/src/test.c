#include "list.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
    list* arglist = list_create();
    for (int i = 1; i < argc; i++) {
        if (!list_prepend(arglist, argv[i])) {
            printf("error list_prepend\n");
            return 1;
        }
    }
    list_print(arglist);
    return 0;
}
