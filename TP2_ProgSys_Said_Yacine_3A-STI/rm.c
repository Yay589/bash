#include<stdio.h>
#include "mini_lib.h"
#define EXIT_FAILURE -1
#define EXIT_SUCCESS 0

int main(int argc, char* argv[]) {
    if(argc!=2) {
        mini_printf("\nusage: rm FileTodelete\n");/*pour l'usage de rm*/
        return EXIT_FAILURE;
    }
    
    int status = remove(argv[1]);
    
    if(status == 0) {
        mini_printf("Successful\n");
        return EXIT_SUCCESS;
    }
    else {
        mini_printf("Unsuccessful\n");
        return EXIT_FAILURE;
    }
}
