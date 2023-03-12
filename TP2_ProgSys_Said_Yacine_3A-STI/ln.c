#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h>
#include "mini_lib.h"

/*générer un executable dont le nom est 'ln'*/
int link(const char *path, const char *newPath);/*appel sys  pour ln*/

int main(int argc, char *argv[]) {
    if (argc != 3) {
        mini_fprintf("Usage: my_ln <existing_file> <new_link>\n");
        return 1;
    }

    if (link(argv[1], argv[2]) != 0) {
        mini_fprintf("Error: Unable to create link\n");
        return 1;
    }

    mini_fprintf("Link created successfully\n");
    return 0;
}
