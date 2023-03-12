
#include <stdio.h> 
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "mini_lib.h"

/*générer un executable dont le nom est 'mkdir'*/


int mainMkdir(int argc,char** argv) {
    int status;
    status = mkdir(argv[1], 0775);
    if (status == -1) {
        mini_printf("Error creating directory!\n");
        mini_exit(EXIT_FAILURE);
    } else {
        mini_printf("Directory created successfully! \n");}
    return 0 ;
}
