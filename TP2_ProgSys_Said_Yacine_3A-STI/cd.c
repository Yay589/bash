#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h>
#include "mini_lib.h"

/* générer un exécutable dont le nom est 'cd' */
/* méthode avec chdir: appel système */

int CdMain(int argc, char *argv[]) {
    if (argc != 2) {
        mini_fprintf("Usage: mini_cd directory\n");
        return 1;
    }

    if (chdir(argv[1]) != 0) {
        mini_fprintf("Error: Unable to change directory to %s\n", argv[1]);
        return 1;
    }

    return 0;
}

/*
#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h>
#include "mini_lib.h"
*/
/*générer un executable dont le nom est 'cd'*/
/*méthode avec chdir: appel système*/
/*
int CdMain(int argc, char *argv[]) {
    if (argc != 2) {
        mini_fprintf("Usage: mini_cd\n");
        return 1;
    }

    if (chdir(argv[1]) != 0) {
        mini_fprintf("Error: Unable to change directory\n");
        return 1;
    }

    return 0;
}
*/